if (precision == 0 && arg_sign == 0
#if defined(HPUX_BUG_COMPATIBLE) || defined(LINUX_COMPATIBLE)
                            && fmt_spec != 'p'
                            /* HPUX 10 man page claims: With conversion character p the result of
                             * converting a zero value with a precision of zero is a null string.
                             * Actually HP returns all zeroes, and Linux returns "(nil)". */
#endif
                       )
                    {
                        /* converted to null string */
                        /* When zero value is formatted with an explicit precision 0,
                           the resulting formatted string is empty (d, i, u, o, x, X, p).   */
                    }
                    else
                    {
                        char f[5];
                        int f_l = 0;
                        f[f_l++] = '%';    /* construct a simple format string for sprintf */
                        if (!length_modifier)
                        { }
                        else if (length_modifier=='2')
                        {
                            f[f_l++] = 'l';
                            f[f_l++] = 'l';
                        }
                        else
                            f[f_l++] = length_modifier;
                        f[f_l++] = fmt_spec;
                        f[f_l++] = '\0';
                        if (fmt_spec == 'p')
                            str_arg_l += sprintf(tmp+str_arg_l, f, ptr_arg);
                        else if (fmt_spec == 'd')
                        {  /* signed */
                            switch (length_modifier)
                            {
                            case '\0':
                            case 'h':
                                str_arg_l+=sprintf(tmp+str_arg_l, f, int_arg);
                                break;
                            case 'l':
                                str_arg_l+=sprintf(tmp+str_arg_l, f, long_arg);
                                break;
#ifdef SNPRINTF_LONGLONG_SUPPORT

                            case '2':
                                str_arg_l+=sprintf(tmp+str_arg_l,f,long_long_arg);
                                break;
#endif

                            }
                        }
                        else
                        {  /* unsigned */
                            switch (length_modifier)
                            {
                            case '\0':
                            case 'h':
                                str_arg_l+=sprintf(tmp+str_arg_l, f, uint_arg);
                                break;
                            case 'l':
                                str_arg_l+=sprintf(tmp+str_arg_l, f, ulong_arg);
                                break;
#ifdef SNPRINTF_LONGLONG_SUPPORT

                            case '2':
                                str_arg_l+=sprintf(tmp+str_arg_l,f,ulong_long_arg);
                                break;
#endif

                            }
                        }
                        /* include the optional minus sign and possible "0x"
                           in the region before the zero padding insertion point */
                        if (zero_padding_insertion_ind < str_arg_l &&
                                tmp[zero_padding_insertion_ind] == '-')
                        {
                            zero_padding_insertion_ind++;
                        }
                        if (zero_padding_insertion_ind+1 < str_arg_l &&
                                tmp[zero_padding_insertion_ind]   == '0' &&
                                (tmp[zero_padding_insertion_ind+1] == 'x' ||
                                 tmp[zero_padding_insertion_ind+1] == 'X') )
                        {
                            zero_padding_insertion_ind += 2;
                        }
                    }
