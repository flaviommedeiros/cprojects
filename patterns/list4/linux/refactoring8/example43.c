struct function memcpy_functions[] = {
	{ .name		= "default",
	  .desc		= "Default memcpy() provided by glibc",
	  .fn.memcpy	= memcpy },

#ifdef HAVE_ARCH_X86_64_SUPPORT
# define MEMCPY_FN(_fn, _name, _desc) {.name = _name, .desc = _desc, .fn.memcpy = _fn},
# include "mem-memcpy-x86-64-asm-def.h"
# undef MEMCPY_FN
#endif

	{ .name = NULL, }
};
