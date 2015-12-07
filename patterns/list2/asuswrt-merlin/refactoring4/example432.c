#  if DCHAR_IS_TCHAR
if (has_width)
#  else
                  else
#  endif
                    {
                      /* Use the entire string, and count the number of
                         bytes.  */
#  if HAVE_WCRTOMB && !defined GNULIB_defined_mbstate_t
                      mbstate_t state;
                      memset (&state, '\0', sizeof (mbstate_t));
#  endif
                      arg_end = arg;
                      characters = 0;
                      for (;;)
                        {
                          char cbuf[64]; /* Assume MB_CUR_MAX <= 64.  */
                          int count;

                          if (*arg_end == 0)
                            /* Found the terminating null wide character.  */
                            break;
#  if HAVE_WCRTOMB && !defined GNULIB_defined_mbstate_t
                          count = wcrtomb (cbuf, *arg_end, &state);
#  else
                          count = wctomb (cbuf, *arg_end);
#  endif
                          if (count < 0)
                            {
                              /* Cannot convert.  */
                              if (!(result == resultbuf || result == NULL))
                                free (result);
                              if (buf_malloced != NULL)
                                free (buf_malloced);
                              CLEANUP ();
                              errno = EILSEQ;
                              return NULL;
                            }
                          arg_end++;
                          characters += count;
                        }
                    }
#  if DCHAR_IS_TCHAR
                  else
                    {
                      /* Use the entire string.  */
                      arg_end = arg + local_wcslen (arg);
                      /* The number of bytes doesn't matter.  */
                      characters = 0;
                    }
