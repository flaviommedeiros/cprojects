if (fhp->handle != INVALID_HANDLE_VALUE &&
		    !LF_ISSET(DB_OSO_RDONLY | DB_OSO_TEMP) &&
		    fhp->trunc_handle == INVALID_HANDLE_VALUE
#ifdef DB_WINCE
		    /* Do not open trunc handle for region files. */
		    && (!LF_ISSET(DB_OSO_REGION))
#endif
		    )
			fhp->trunc_handle = CreateFile(
			    tname, access, share, NULL, OPEN_EXISTING, attr, 0);
