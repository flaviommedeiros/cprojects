if (fhp->handle == INVALID_HANDLE_VALUE ||
		    (!LF_ISSET(DB_OSO_RDONLY | DB_OSO_TEMP) &&
		    fhp->trunc_handle == INVALID_HANDLE_VALUE
#ifdef DB_WINCE
		    /* Do not open trunc handle for region files. */
		    && (!LF_ISSET(DB_OSO_REGION))
#endif
		    ))
#endif
		{
			/*
			 * If it's a "temporary" error, we retry up to 3 times,
			 * waiting up to 12 seconds.  While it's not a problem
			 * if we can't open a database, an inability to open a
			 * log file is cause for serious dismay.
			 */
			ret = __os_posix_err(__os_get_syserr());
			if ((ret != ENFILE && ret != EMFILE && ret != ENOSPC) ||
			    nrepeat > 3)
				goto err;

			__os_yield(env, nrepeat * 2, 0);
		} else
			break;
