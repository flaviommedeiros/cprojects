#ifdef HAVE_MMAP
if (use_mmap)
	munmap ((caddr_t) data, size);
      else
#endif
	free (data);
