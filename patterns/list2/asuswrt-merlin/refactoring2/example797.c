#ifdef ERANGE
if (e != ERANGE)
#endif
	      {
		errno = failure_errno = e;
		p = 0;
		break;
	      }
