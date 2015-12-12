if ((fd2 = open (___CAST(___STRING_TYPE(___COPY_FILE_PATH_CE_SELECT),
                                       cpath2),
#ifdef O_BINARY
                               O_BINARY|
#endif
                               O_WRONLY|O_CREAT|O_EXCL,
                               0777)) < 0)
                e = fnf_or_err_code_from_errno ();
              else
                {
                  char buffer[4096];
                  int nr;
                  int nw;

                  for (;;)
                    {
                      nr = read (fd1, buffer, sizeof (buffer));

                      if (nr == 0)
                        break;

                      if (nr < 0 || (nw = write (fd2, buffer, nr)) < 0)
                        {
                          e = err_code_from_errno ();
                          break;
                        }

                      if (nw != nr)
                        {
                          e = ___FIX(___UNKNOWN_ERR);
                          break;
                        }
                    }

                  if (close (fd2) < 0 && e != ___FIX(___NO_ERR))
                    e = err_code_from_errno ();
                }
