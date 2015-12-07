#if defined (VISIBLE_STATS)
if (rl_filename_completion_desired && (rl_visible_stats || _rl_complete_mark_directories))
#else
 if (rl_filename_completion_desired && _rl_complete_mark_directories)
#endif
    {
      /* If to_print != full_pathname, to_print is the basename of the
	 path passed.  In this case, we try to expand the directory
	 name before checking for the stat character. */
      if (to_print != full_pathname)
	{
	  /* Terminate the directory name. */
	  c = to_print[-1];
	  to_print[-1] = '\0';

	  /* If setting the last slash in full_pathname to a NUL results in
	     full_pathname being the empty string, we are trying to complete
	     files in the root directory.  If we pass a null string to the
	     bash directory completion hook, for example, it will expand it
	     to the current directory.  We just want the `/'. */
	  if (full_pathname == 0 || *full_pathname == 0)
	    dn = "/";
	  else if (full_pathname[0] != '/')
	    dn = full_pathname;
	  else if (full_pathname[1] == 0)
	    dn = "//";		/* restore trailing slash to `//' */
	  else if (full_pathname[1] == '/' && full_pathname[2] == 0)
	    dn = "/";		/* don't turn /// into // */
	  else
	    dn = full_pathname;
	  s = tilde_expand (dn);
	  if (rl_directory_completion_hook)
	    (*rl_directory_completion_hook) (&s);

	  slen = strlen (s);
	  tlen = strlen (to_print);
	  new_full_pathname = (char *)xmalloc (slen + tlen + 2);
	  strcpy (new_full_pathname, s);
	  if (s[slen - 1] == '/')
	    slen--;
	  else
	    new_full_pathname[slen] = '/';
	  new_full_pathname[slen] = '/';
	  strcpy (new_full_pathname + slen + 1, to_print);

#if defined (VISIBLE_STATS)
	  if (rl_visible_stats)
	    extension_char = stat_char (new_full_pathname);
	  else
#endif
	  if (path_isdir (new_full_pathname))
	    extension_char = '/';

	  free (new_full_pathname);
	  to_print[-1] = c;
	}
      else
	{
	  s = tilde_expand (full_pathname);
#if defined (VISIBLE_STATS)
	  if (rl_visible_stats)
	    extension_char = stat_char (s);
	  else
#endif
	    if (path_isdir (s))
	      extension_char = '/';
	}

      free (s);
      if (extension_char)
	{
	  putc (extension_char, rl_outstream);
	  printed_len++;
	}
    }
