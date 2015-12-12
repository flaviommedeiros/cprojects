static const struct function memset_functions[] = {
	{ .name		= "default",
	  .desc		= "Default memset() provided by glibc",
	  .fn.memset	= memset },

#ifdef HAVE_ARCH_X86_64_SUPPORT
# define MEMSET_FN(_fn, _name, _desc) { .name = _name, .desc = _desc, .fn.memset = _fn },
# include "mem-memset-x86-64-asm-def.h"
# undef MEMSET_FN
#endif

	{ .name = NULL, }
};
