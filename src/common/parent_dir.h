#ifndef SRC_COMMON_PARENT_DIR_H_
#define SRC_COMMON_PARENT_DIR_H_
#include <libgen.h>
#include <linux/limits.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * @brief Returns the absolute parent_dir path of parent_depth.
 *
 * @param parent_dir String where to save the value of parent_dir.
 * @param path Relative path from which should be taken parent_dir.
 * @param parent_depth Depth of parent directory (if is 0 will return file).
 */
#define parent_dir_def(parent_dir, path, parent_depth)                        \
	char path_buffer[PATH_MAX];                                           \
	char *parent_dir = realpath(path, path_buffer);                       \
	for (unsigned int i = 0; i < parent_depth && strcmp(parent_dir, "/"); \
	     i++) {                                                           \
		parent_dir = dirname(parent_dir);                             \
	}

#endif // SRC_COMMON_PARENT_DIR_H_
