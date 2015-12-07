if ((b->type == bp_catch_unload)
#if defined(SOLIB_HAVE_UNLOAD_EVENT)
	&& (!SOLIB_HAVE_UNLOAD_EVENT (PIDGET (inferior_ptid))
	    || ((b->dll_pathname != NULL)
		&& (strcmp (b->dll_pathname, 
			    SOLIB_UNLOADED_LIBRARY_PATHNAME (
			      PIDGET (inferior_ptid)))
		    != 0)))
#endif
      )
      continue;
