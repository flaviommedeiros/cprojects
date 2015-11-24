#ifdef EINTR
if (errno == EINTR)
				i=0;
			else
#endif
			        /* This is really a bad error - very bad
				 * It will stuff-up both ends. */
				return(-1);
