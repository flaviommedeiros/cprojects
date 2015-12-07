if (fmt_spec == 'p'
                                 /* HPUX 10: for an alternate form of p conversion,
                                  *          a nonzero result is prefixed by 0x. */
#ifndef HPUX_BUG_COMPATIBLE
                                 /* Actually it uses 0x prefix even for a zero value. */
                                 && arg_sign != 0
#endif
                                )
                        {
                            tmp[str_arg_l++] = '0';
                            tmp[str_arg_l++] = 'x';
                        }
