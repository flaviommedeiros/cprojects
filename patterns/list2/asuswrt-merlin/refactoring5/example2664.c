# ifdef _POSIX_MAPPED_FILES
if (domain->use_mmap)
    munmap ((void *) domain->data, domain->mmap_size);
  else
# endif	/* _POSIX_MAPPED_FILES */
    free ((void *) domain->data);
