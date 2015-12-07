if ((b->type == bp_catch_load)
#if defined(SOLIB_HAVE_LOAD_EVENT)
	&& (!SOLIB_HAVE_LOAD_EVENT (PIDGET (inferior_ptid))
	    || ((b->dll_pathname != NULL)
		&& (strcmp (b->dll_pathname, 
			    SOLIB_LOADED_LIBRARY_PATHNAME (
			      PIDGET (inferior_ptid)))
		    != 0)))
#endif
      )
      continue;
