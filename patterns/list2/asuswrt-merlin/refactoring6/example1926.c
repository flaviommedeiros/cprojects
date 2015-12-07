if (!filename_seen (ps->filename, 1, &first)
#if HAVE_DOS_BASED_FILE_SYSTEM
	      && strncasecmp (ps->filename, text, text_len) == 0
#else
	      && strncmp (ps->filename, text, text_len) == 0
#endif
	      )
	    {
	      /* This file matches for a completion; add it to the
		 current list of matches.  */
	      add_filename_to_list (ps->filename, text, word,
				    &list, &list_used, &list_alloced);

	    }
	  else
	    {
	      base_name = lbasename (ps->filename);
	      if (base_name != ps->filename
		  && !filename_seen (base_name, 1, &first)
#if HAVE_DOS_BASED_FILE_SYSTEM
		  && strncasecmp (base_name, text, text_len) == 0
#else
		  && strncmp (base_name, text, text_len) == 0
#endif
		  )
		add_filename_to_list (base_name, text, word,
				      &list, &list_used, &list_alloced);
	    }
