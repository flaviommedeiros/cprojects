struct routine routines[] = {
	{ "default",
	  "Default memcpy() provided by glibc",
	  memcpy },
#ifdef ARCH_X86_64

#define MEMCPY_FN(fn, name, desc) { name, desc, fn },
#include "mem-memcpy-x86-64-asm-def.h"
#undef MEMCPY_FN

#endif

	{ NULL,
	  NULL,
	  NULL   }
};
