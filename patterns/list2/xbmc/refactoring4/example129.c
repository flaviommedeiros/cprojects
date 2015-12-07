#ifdef __BIG_ENDIAN__
if (((struct mach_header *)module)->magic == MH_MAGIC)
#else
    if (((struct mach_header *)module)->magic == MH_CIGAM)
#endif
	{
	  LT_DLMUTEX_SETERROR("Can not close a dylib");
	  retCode = 1;
	}
	else
	{
#if 1
/* Currently, if a module contains c++ static destructors and it is unloaded, we
   get a segfault in atexit(), due to compiler and dynamic loader differences of
   opinion, this works around that.
*/
		if ((const struct section *)NULL !=
		   getsectbynamefromheader(lt_int_dyld_get_mach_header_from_nsmodule(module),
		   "__DATA","__mod_term_func"))
		{
			flags += NSUNLINKMODULE_OPTION_KEEP_MEMORY_MAPPED;
		}
#endif
#ifdef __ppc__
			flags += NSUNLINKMODULE_OPTION_RESET_LAZY_REFERENCES;
#endif
		if (!NSUnLinkModule(module,flags))
		{
			retCode=1;
			LT_DLMUTEX_SETERROR (lt_int_dyld_error(LT_DLSTRERROR(CANNOT_CLOSE)));
		}
	}
