# if NEED_PRINTF_LONG_DOUBLE
if (type == TYPE_LONGDOUBLE)
#  endif
                  if (dp->conversion == 'f' || dp->conversion == 'F')
                    {
                      long double arg = a.arg[dp->arg_index].a.a_longdouble;
                      if (!(isnanl (arg) || arg + arg == arg))
                        {
                          /* arg is finite and nonzero.  */
                          int exponent = floorlog10l (arg < 0 ? -arg : arg);
                          if (exponent >= 0 && tmp_length < exponent + precision)
                            tmp_length = exponent + precision;
                        }
                    }
