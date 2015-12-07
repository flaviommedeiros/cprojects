#ifdef HAVE_MMAP
if (use_mmap)
	munmap ((void *) data, size);
      else
#endif
	free (data);
