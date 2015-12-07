if (ext && ((streq (ext, archive_ext))
#if defined(LT_MODULE_EXT)
	     || (streq (ext, shlib_ext))
#endif
    ))
    {
      return 1;
    }
