if (! access (nstore, X_OK)
#ifdef HAVE_HOST_EXECUTABLE_SUFFIX
                      || ! access (strcat (nstore, HOST_EXECUTABLE_SUFFIX), X_OK)
#endif
		      )
		    {
		      progname = nstore;
		      break;
		    }
