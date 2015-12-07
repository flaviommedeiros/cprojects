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
          if (tryall_dlopen (&newhandle, filename) != 0)
            {
              newhandle = NULL;
            }
	}
