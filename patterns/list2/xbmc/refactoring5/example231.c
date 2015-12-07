#ifdef TIOCGWINSZ
if (!ioctl(0, TIOCGWINSZ, &size)) {
    SLtt_Screen_Cols=size.ws_col;
    SLtt_Screen_Rows=size.ws_row;
  } else
#endif
  {
    SLtt_Screen_Cols=atoi(getenv("COLUMNS"));
    SLtt_Screen_Rows=atoi(getenv("LINES"));
  }
