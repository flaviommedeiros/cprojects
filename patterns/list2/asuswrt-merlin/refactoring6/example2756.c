if ((dir || (!find_handle (user_search_path, base_name,
				 &newhandle, advise)
		   && !find_handle (getenv (LTDL_SEARCHPATH_VAR), base_name,
				    &newhandle, advise)
#if defined(LT_MODULE_PATH_VAR)
		   && !find_handle (getenv (LT_MODULE_PATH_VAR), base_name,
				    &newhandle, advise)
#endif
#if defined(LT_DLSEARCH_PATH)
		   && !find_handle (sys_dlsearch_path, base_name,
				    &newhandle, advise)
#endif
		   )))
	{
	  if (tryall_dlopen (&newhandle, attempt, advise, 0) != 0)
	    {
	      newhandle = NULL;
	    }
	}
