int arg_encoding
   ___P((___STRING_TYPE(___STREAM_OPEN_PROCESS_CE_SELECT) arg,
         int *len_increase,
         ___BOOL *need_quotes),
        (arg,
         len_increase,
         need_quotes)
___STRING_TYPE(___STREAM_OPEN_PROCESS_CE_SELECT) arg;
int *len_increase;
___BOOL *need_quotes;)
{
  int len = 0;

  while (arg[len] != ___UNICODE_NUL)
    len++;

#ifdef ___ESCAPE_PROCESS_ARGS

  {
    int j = len;
    int increase = 0;
    ___BOOL quotes = FALSE;
    ___BOOL double_backslash = TRUE;

    while (--j >= 0)
      {
        ___CHAR_TYPE(___STREAM_OPEN_PROCESS_CE_SELECT) c = arg[j];
        if (c == ___UNICODE_DOUBLEQUOTE ||
            (double_backslash && c == ___UNICODE_BACKSLASH))
          {
            double_backslash = TRUE;
            increase++; /* space for backslash */
          }
        else
          {
            double_backslash = FALSE;
            if (c == ___UNICODE_SPACE)
              quotes = TRUE;
          }
      }

    if (increase > 0)
      quotes = TRUE;

    if (quotes)
      increase += 2; /* space for quotes */

    *len_increase = increase;
    *need_quotes = quotes;
  }

#else

  *len_increase = 0;
  *need_quotes = FALSE;

#endif

  return len;
}
