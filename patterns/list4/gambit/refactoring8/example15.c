argv_to_ccmd
   ___P((___STRING_TYPE(___STREAM_OPEN_PROCESS_CE_SELECT) *argv),
        (argv)
___STRING_TYPE(___STREAM_OPEN_PROCESS_CE_SELECT) *argv;)
{
  ___STRING_TYPE(___STREAM_OPEN_PROCESS_CE_SELECT) ccmd;
  int ccmd_len = 0;
  int i = 0;
  int len_increase;
  ___BOOL need_quotes;
  ___STRING_TYPE(___STREAM_OPEN_PROCESS_CE_SELECT) arg;

  while ((arg = argv[i]) != NULL)
    {
      ccmd_len += arg_encoding (arg, &len_increase, &need_quotes);
      ccmd_len += len_increase + 1;
      i++;
    }

  ccmd = ___CAST(___STRING_TYPE(___STREAM_OPEN_PROCESS_CE_SELECT),
                 ___alloc_mem (ccmd_len * sizeof (*ccmd)));

  if (ccmd != NULL)
    {
      ccmd[--ccmd_len] = ___UNICODE_NUL;

      while (--i >= 0)
        {
          int j;

          arg = argv[i];

          j = arg_encoding (arg, &len_increase, &need_quotes);

#ifdef ___ESCAPE_PROCESS_ARGS

          {
            ___BOOL double_backslash = TRUE;

            if (need_quotes)
              ccmd[--ccmd_len] = ___UNICODE_DOUBLEQUOTE;

            while (--j >= 0)
              {
                ___CHAR_TYPE(___STREAM_OPEN_PROCESS_CE_SELECT) c = arg[j];
                ccmd[--ccmd_len] = c;
                if (c == ___UNICODE_DOUBLEQUOTE ||
                    (double_backslash && c == ___UNICODE_BACKSLASH))
                  {
                    ccmd[--ccmd_len] = ___UNICODE_BACKSLASH;
                    double_backslash = TRUE;
                  }
                else
                  double_backslash = FALSE;
              }

            if (need_quotes)
              ccmd[--ccmd_len] = ___UNICODE_DOUBLEQUOTE;
          }

#else

          while (--j >= 0)
            {
              ___CHAR_TYPE(___STREAM_OPEN_PROCESS_CE_SELECT) c = arg[j];
              ccmd[--ccmd_len] = c;
            }

#endif

          if (i > 0)
            ccmd[--ccmd_len] = ___UNICODE_SPACE;
        }
    }

  return ccmd;
}
