if (!filename_seen (s->filename, 1, &first)
#if HAVE_DOS_BASED_FILE_SYSTEM
	  && strncasecmp (s->filename, text, text_len) == 0
#else
	  && strncmp (s->filename, text, text_len) == 0
#endif
	  )
	{
	  /* This file matches for a completion; add it to the current
	     list of matches.  */
	  add_filename_to_list (s->filename, text, word,
				&list, &list_used, &list_alloced);
	}
      else
	{
	  /* NOTE: We allow the user to type a base name when the
	     debug info records leading directories, but not the other
	     way around.  This is what subroutines of breakpoint
	     command do when they parse file names.  */
	  base_name = lbasename (s->filename);
	  if (base_name != s->filename
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
