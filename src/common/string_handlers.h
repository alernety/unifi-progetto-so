#ifndef SRC_COMMON_STRING_HANDLERS_H_
#define SRC_COMMON_STRING_HANDLERS_H_
#include <sys/types.h>

/**
 * @brief Get the malloc string from file, using file.
 *
 * @param file Path to the file to read.
 * @return char* String got from the file with file,
 *         allocated with malloc.
 */
char *get_malloc_string_from(const char *file);

/**
 * @brief Get the number of tokens, split str by delim.
 *
 * @param str String to count tokens in.
 * @param delim Delimiter, by which will be counted tokens.
 * @return int Number of tokens found split by delimiter.
 */
int get_number_of_tokens(const char *str, const char *delim);

/**
 * @brief Get the malloc token list, split string by delimeter and
 *        returns an array of strings, created by malloc.
 *
 * @param string_to_split String with delimiters to split.
 * @param delim Delimiter used in string.
 * @return char** Array of malloc strings.
 */
char **get_malloc_token_list(char *string_to_split, const char *delim);

/**
 * @brief Get the malloc token list, split string by delimeter and
 *        returns an array of strings, created by malloc.
 *
 * @param string_to_split String with delimiters to split.
 * @param delim Delimiter used in string.
 * @param token_number Max number of tokens to get from string_to_split.
 * @return char** Array of malloc strings, limited by token_number.
 */
char **get_malloc_token_list_number(char *string_to_split, const char *delim,
				    size_t tokens_number);

/**
 * @brief Extract integer from string.
 *
 * @param string_with_integer String contains integer.
 * @return int Integer, got from string_with_integer. If integer not found
 *         will return -1.
 */
int get_integer_from(char *string_with_integer);

/**
 * @brief Converts all string to uppercase.
 *
 * @param string_to_handle String to convert to uppercase.
 * @return char* Uppercase string.
 */
char *to_upper(char *string_to_handle);

#endif // SRC_COMMON_STRING_HANDLERS_H_
