#ifdef HAVE_MUNMAP
if ((*entry)->munmap_length > 0)
	    munmap ((*entry)->buffer, (*entry)->munmap_length);
	  else
#endif
	    zfree ((*entry)->buffer);
