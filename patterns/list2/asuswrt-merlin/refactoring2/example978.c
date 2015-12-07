#ifdef NO_XMALLOC
if (shorter != NULL)
#endif
              {
                memcpy (shorter, argv0, argv0_len - exeext_len - 4);
                if (sizeof (EXEEXT) > sizeof (""))
                  memcpy (shorter + argv0_len - exeext_len - 4,
                          argv0 + argv0_len - exeext_len - 4,
                          exeext_len);
                shorter[argv0_len - 4] = '\0';
                argv0_stripped = shorter;
              }
