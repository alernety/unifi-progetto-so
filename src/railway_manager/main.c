#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "common/alloc_macro.h"
#include "common/parent_dir.h"
#include "railway_manager/default_values.h"

#define DEFAULT_FILE_NAME 0
#define DEFAULT_FILE_STRING 1

int main(int argc, char const *argv[])
{
	const char *format_string =
		"\033[31mNot enough arguments! Example of use:\033[0m\n"
		"\n"
		"Usage: %s MODE [RBC] MAP\n\n"
		"\033[36mMODE\033[0m possible values are:\n"
		"    \033[36mETCS1\033[0m    - program has to be used without server\n"
		"    \033[36mETCS2\033[0m    - program has to be used with server RBC\n"
		"\n"
		"\033[36mRBC\033[0m used to activate server\n"
		"\n"
		"\033[36mMAP\033[0m possible values are:\n"
		"    \033[36mMAPPA1\033[0m   - manage trains with map one \n"
		"    \033[36mMAPPA2\033[0m   - manage trains with map two\n";
	size_t help_length = strlen(format_string) + strlen(argv[0]) + 1;
	malloc_macro_def(char *, help_str, help_length);
	char *map_name;
	bool is_rbc = false;
	bool is_etcs2 = false;
	snprintf(help_str, help_length, format_string, argv[0]);
	switch (argc) {
	case 3: {
		bool is_not_etcs = strcmp(argv[1], "ETCS1") &&
				   strcmp(argv[1], "ETCS2");
		bool is_not_map = strcmp(argv[2], "MAPPA1") &&
				  strcmp(argv[2], "MAPPA2");
		if (is_not_etcs || is_not_map) {
			printf("%s", help_str);
			exit(EXIT_FAILURE);
		}
		is_etcs2 = !strcmp(argv[1], "ETCS2");
		map_name = strdup(argv[2]);
		break;
	}
	case 4: {
		bool is_not_map = strcmp(argv[3], "MAPPA1") &&
				  strcmp(argv[3], "MAPPA2");
		if (strcmp(argv[1], "ETCS2") || strcmp(argv[2], "RBC") ||
		    is_not_map) {
			printf("%s", help_str);
			exit(EXIT_FAILURE);
		}
		map_name = strdup(argv[3]);
		is_etcs2 = !strcmp(argv[1], "ETCS2");
		is_rbc = !strcmp(argv[2], "RBC");
		break;
	}
	default:
		printf("%s", help_str);
		exit(EXIT_FAILURE);
		break;
	}
	free(help_str);

	parent_dir_def(project_path, argv[0], 2);
	if (chdir(project_path) == -1) {
		perror("change directory");
		abort();
	}

	const char *files[][2] = { { "tmp/railway.txt",
				     RAILWAY_DEFAULT_STRING },
				   { "tmp/MAPPA1", MAPPA1_DEFAULT_STRING },
				   { "tmp/MAPPA2", MAPPA2_DEFAULT_STRING } };
	size_t files_length = sizeof(files) / sizeof(files[0]);

	// Create or rewrite map
	for (size_t index = 0; index < files_length; index++) {
		const char *file_name = files[index][DEFAULT_FILE_NAME];
		if (index > 0 && strcmp(map_name, file_name + strlen("tmp/"))) {
			continue;
		}
		if (index) {
			map_name = strdup(file_name);
		}
		const char *file_string = files[index][DEFAULT_FILE_STRING];
		int fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC,
			      S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
		if (fd < 0) {
			size_t error_length =
				snprintf(NULL, 0, "open or create '%s' file",
					 file_name) +
				1;
			malloc_macro_def(char *, error, error_length);
			snprintf(error, error_length,
				 "open or create '%s' file", file_name);
			perror(error);
			abort();
		}
		size_t string_length = strlen(file_string);
		size_t file_length = write(fd, file_string, string_length);
		if (file_length != string_length) {
			size_t error_length = snprintf(NULL, 0,
						       "write '%s' file",
						       file_name) +
					      1;
			malloc_macro_def(char *, error, error_length);
			snprintf(error, error_length, "write '%s' file",
				 file_name);
			perror(error);
			abort();
		}
		close(fd);
	}

	pid_t pid = 0;
	// Not fork only if it is an ETCS2 mode called without RBC.
	// Need this to not create duplicate process PADRE_TRENI.
	bool is_only_REGISTRO = is_etcs2 & !is_rbc;
	if (!is_only_REGISTRO) {
		pid = fork();
	}
	if (pid < 0) {
		perror("fork");
		abort();
	} else if (is_rbc && pid != 0) {
		execl("bin/RBC", "bin/RBC", NULL);
	} else if (pid != 0 || is_only_REGISTRO) {
		execl("bin/REGISTRO", "bin/REGISTRO", map_name, NULL);
	} else {
		const char *socket_path = is_etcs2 ? "tmp/rbc" : "";
		const char *trains_number =
			strcmp(map_name, "tmp/MAPPA1") ? "5" : "4";
		execl("bin/PADRE_TRENI", "bin/PADRE_TRENI", trains_number,
		      socket_path, "1", NULL);
	}
	free(map_name);

	return EXIT_SUCCESS;
}