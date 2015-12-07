#if defined(TUI)
if (!tui_get_command_dimension (&chars_per_line, &lines_per_page))
#endif
    {
      int rows, cols;

#if defined(__GO32__)
      rows = ScreenRows ();
      cols = ScreenCols ();
      lines_per_page = rows;
      chars_per_line = cols;
#else
      /* Make sure Readline has initialized its terminal settings.  */
      rl_reset_terminal (NULL);

      /* Get the screen size from Readline.  */
      rl_get_screen_size (&rows, &cols);
      lines_per_page = rows;
      chars_per_line = cols;

      /* Readline should have fetched the termcap entry for us.  */
      if (tgetnum ("li") < 0 || getenv ("EMACS"))
	{
	  /* The number of lines per page is not mentioned in the
	     terminal description.  This probably means that paging is
	     not useful (e.g. emacs shell window), so disable paging.  */
	  lines_per_page = UINT_MAX;
	}

      /* FIXME: Get rid of this junk.  */
#if defined(SIGWINCH) && defined(SIGWINCH_HANDLER)
      SIGWINCH_HANDLER (SIGWINCH);
#endif

      /* If the output is not a terminal, don't paginate it.  */
      if (!ui_file_isatty (gdb_stdout))
	lines_per_page = UINT_MAX;
#endif
    }
