___HIDDEN ___SCMOBJ parse_windows_command_line
   ___P((___STRING_TYPE(___CMDLINE_CE_SELECT) cmdline,
         ___UCS_2STRING **argv_return),
        (cmdline,
         argv_return)
___STRING_TYPE(___CMDLINE_CE_SELECT) cmdline;
___UCS_2STRING **argv_return;)
{
  int argc = 0;
  ___UCS_2STRING *argv = 0;
  ___UCS_2STRING args = 0;
  int total_arg_len = 0;
  int pass;

  for (pass=0; pass<2; pass++)
    {
      int in_double_quotes;
      int nb_backslashes;
      ___STRING_TYPE(___CMDLINE_CE_SELECT) p;
      ___CHAR_TYPE(___CMDLINE_CE_SELECT) c;

      if (pass != 0)
        {
          if ((argv = ___CAST(___UCS_2STRING*,
                              ___alloc_mem ((argc + 1)
                                            * sizeof (___UCS_2STRING)))) == 0)
            return ___FIX(___HEAP_OVERFLOW_ERR);

          if (total_arg_len > 0)
            {
              if ((args = ___CAST(___UCS_2STRING,
                                  ___alloc_mem (total_arg_len
                                                * sizeof (___UCS_2)))) == 0)
                {
                  ___free_mem (argv);
                  return ___FIX(___HEAP_OVERFLOW_ERR);
                }
            }
        }

      total_arg_len = 0;
      argc = 0;
      p = cmdline;

      for (;;)
        {
          while ((c = *p) != '\0' && c <= ' ')
            p++;

          if (c == '\0')
            break;

          in_double_quotes = 0;
          nb_backslashes = 0;

          if (pass != 0)
            argv[argc] = args;

          while ((c = *p) != '\0' && (in_double_quotes || c > ' '))
            {
              if (c == '\\')
                nb_backslashes++;
              else
                {
                  if (c != '"')
                    nb_backslashes = (nb_backslashes<<1) + 1;
                  else
                    {
                      if ((nb_backslashes & 1) == 0)
                        in_double_quotes ^= 1;
#ifndef PROCESS_PROGRAM_LIKE_OTHER_ARGS
                      if (argc == 0)
                        nb_backslashes = (nb_backslashes<<1) + 1;
#endif
                    }

                  total_arg_len += ((nb_backslashes+1)>>1);

                  if (pass != 0)
                    {
                      while (nb_backslashes > 1)
                        {
                          *args++ = '\\';
                          nb_backslashes -= 2;
                        }
                      if (nb_backslashes != 0)
                        *args++ = c;
                    }

                  nb_backslashes = 0;
                }
              p++;
            }

          total_arg_len += nb_backslashes+1;

          if (pass != 0)
            {
              while (nb_backslashes-- > 0)
                *args++ = '\\';
              *args++ = '\0';
            }

          argc++;
        }
    }

  argv[argc] = 0;

  *argv_return = argv;

  return ___FIX(___NO_ERR);
}
