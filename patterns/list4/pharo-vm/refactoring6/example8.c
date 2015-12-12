if ((dir || (!find_handle (user_search_path, base_name, &newhandle)
		   && !find_handle (getenv (LTDL_SEARCHPATH_VAR), base_name,
				    &newhandle)
#ifdef LTDL_SHLIBPATH_VAR
		   && !find_handle (getenv (LTDL_SHLIBPATH_VAR), base_name,
				    &newhandle)
#endif
#ifdef LTDL_SYSSEARCHPATH
		   && !find_handle (sys_search_path, base_name, &newhandle)
#endif
		   )))
	{
	  // Directory component was specified, or all find_handle() calls
	  // failed to find the lib.  This is our last try.
	  errors = tryall_dlopen (&newhandle, filename);
	}
