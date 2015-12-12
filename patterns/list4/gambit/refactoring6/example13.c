if ((fd = open (term_name,
#ifdef LINEEDITOR_WITH_NONBLOCKING_IO
                        O_NONBLOCK |
#endif
#ifdef O_BINARY
                        O_BINARY |
#endif
                        O_RDWR,
                        0))
            < 0)
          {
#ifdef ENXIO
            if (errno == ENXIO)
              {
                /*
                 * There is no controlling terminal, so console output
                 * has to be redirected.  This is done by calling
                 * ___write_console_fallback which will send the output
                 * to stderr, a log file, etc.
                 */

                static char msg[] =
                  "*** No controlling terminal (try using the -:d- runtime option)\n";

                ___write_console_fallback (msg, sizeof(msg)-1);

                fd = -1; /* redirect subsequent console output */
              }
            else
#endif
            return fnf_or_err_code_from_errno ();
          }
