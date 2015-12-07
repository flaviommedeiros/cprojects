# ifdef _LIBC
if (__wcscoll (workp, d) > 0)
# else
		    if (wcscoll (workp, d) > 0)
# endif
		      {
			workp += length + 1;
			break;
		      }
