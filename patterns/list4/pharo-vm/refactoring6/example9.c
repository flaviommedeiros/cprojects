if (ext && ((strcmp (ext, archive_ext) == 0)
#ifdef LTDL_SHLIB_EXT
	      || (strcmp (ext, shlib_ext) == 0)
#endif
      ))
    {
      return lt_dlopen (filename);
    }
