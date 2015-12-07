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
