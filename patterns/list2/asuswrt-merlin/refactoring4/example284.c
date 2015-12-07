#if defined (DISPLAY_TABS)
if ((CTRL_CHAR (c) && c != '\t') || c == RUBOUT)
#else
  if (CTRL_CHAR (c) || c == RUBOUT)
#endif /* !DISPLAY_TABS */
    {
      fprintf (rl_outstream, "C-");
      n += 2;
      c = CTRL_CHAR (c) ? UNCTRL (c) : '?';
    }
