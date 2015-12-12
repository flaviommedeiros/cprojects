if (length &&
#ifdef FN_DEVCHAR
      buff[length - 1] != FN_DEVCHAR &&
#endif
      buff[length - 1] != FN_LIBCHAR && buff[length - 1] != '/')
  {
    /* we need reserve 2 bytes for the trailing slash and the zero */
    if (length >= sizeof (buff) - 1)
      length= sizeof (buff) - 2;
    buff[length]= FN_LIBCHAR;
    buff[length + 1]= '\0';
  }
