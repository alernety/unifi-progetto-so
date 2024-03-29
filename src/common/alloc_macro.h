#ifndef SRC_COMMON_ALLOC_MACRO_H_
#define SRC_COMMON_ALLOC_MACRO_H_
#include <stdio.h>
#include <stdlib.h>

#define alloc_macro_def(alloc_function_call, def_type, cast_type, variable) \
	def_type variable = (cast_type)alloc_function_call;                 \
	if (!variable) {                                                    \
		perror("Memory allocation failed!\n");                      \
		abort();                                                    \
	}

#define malloc_macro(cast_type, variable, size) \
	alloc_macro_def(malloc(size + 1), , cast_type, variable)

#define malloc_macro_def(cast_type, variable, size) \
	alloc_macro_def(malloc(size + 1), cast_type, cast_type, variable)

#define realloc_macro(cast_type, variable, size) \
	alloc_macro_def(realloc(variable, size + 1), , cast_type, variable)

#endif // SRC_COMMON_ALLOC_MACRO_H_
