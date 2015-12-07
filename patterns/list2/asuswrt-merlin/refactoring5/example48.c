#ifdef CORE_MAGIC64
if (coreout.c_magic == (int) CORE_MAGIC64)
    {
      if (! do_sections64 (abfd, & coreout))
	goto fail;
    }
  else
#endif
    if (! do_sections (abfd, & coreout))
      goto fail;
