if ((ufile_ptr) NBPG * (UPAGES + u.u_dsize
#ifdef TRAD_CORE_DSIZE_INCLUDES_TSIZE
			    - u.u_tsize
#endif
			    + u.u_ssize)
	> (ufile_ptr) statbuf.st_size)
      {
	bfd_set_error (bfd_error_wrong_format);
	return 0;
      }
