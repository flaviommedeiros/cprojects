if (filespeclen >
#ifdef NAML$C_MAXRSS
	  NAML$C_MAXRSS
#else
	  255
#endif
	  )
	{
	  errno = ENAMETOOLONG;
	  return 0;
	}
