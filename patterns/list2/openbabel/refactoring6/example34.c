if (alternate_form && fmt_spec == 'o'
#ifdef HPUX_COMPATIBLE                                  /* ("%#.o",0) -> ""  */
                                && (str_arg_l > 0)
#endif
#ifdef DIGITAL_UNIX_BUG_COMPATIBLE                      /* ("%#o",0) -> "00" */
#else
                                /* unless zero is already the first character */
                                && !(zero_padding_insertion_ind < str_arg_l
                                     && tmp[zero_padding_insertion_ind] == '0')
#endif
                           )
                        {        /* assure leading zero for alternate-form octal numbers */
                            if (!precision_specified || precision < num_of_digits+1)
                            {
                                /* precision is increased to force the first character to be zero,
                                   except if a zero value is formatted with an explicit precision
                                   of zero */
                                precision = num_of_digits+1;
                                precision_specified = 1;
                            }
                        }
