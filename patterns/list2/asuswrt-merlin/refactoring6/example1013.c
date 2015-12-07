if (((ufile_ptr) NBPG * (UPAGES + u.u_dsize + u.u_ssize)
#ifdef TRAD_CORE_EXTRA_SIZE_ALLOWED
	/* Some systems write the file too big.  */
	 + TRAD_CORE_EXTRA_SIZE_ALLOWED
#endif
	 )
	< (ufile_ptr) statbuf.st_size)
      {
	/* The file is too big.  Maybe it's not a core file
	   or we otherwise have bad values for u_dsize and u_ssize).  */
	bfd_set_error (bfd_error_wrong_format);
	return 0;
      }
