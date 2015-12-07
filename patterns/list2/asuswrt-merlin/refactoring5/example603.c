#ifdef HAVE_MMAP
if (fm->mmap_p)
    {
      munmap (fm->content, fm->length);
    }
  else
#endif
    {
      xfree (fm->content);
    }
