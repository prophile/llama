#ifndef _INCLUDED_LLAMA_INTERNAL
#define _INCLUDED_LLAMA_INTERNAL

#include <stdbool.h>

#define MEMOISE(type, value) static type __val; static bool __found = false;\
if (!__found)\
{\
	__val = value;\
	__found = true;\
}\
return __val

#endif
