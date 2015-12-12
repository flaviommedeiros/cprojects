static const struct routine routines[] = {
	{ "default",
	  "Default memset() provided by glibc",
	  memset },
#ifdef ARCH_X86_64

#define MEMSET_FN(fn, name, desc) { name, desc, fn },
#include "mem-memset-x86-64-asm-def.h"
#undef MEMSET_FN

#endif

	{ NULL,
	  NULL,
	  NULL   }
};
