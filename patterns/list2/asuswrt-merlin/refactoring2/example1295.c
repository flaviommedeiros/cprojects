# if NEED_PRINTF_DOUBLE
if (type == TYPE_DOUBLE)
#  endif
                  if (dp->conversion == 'f' || dp->conversion == 'F')
                    {
                      double arg = a.arg[dp->arg_index].a.a_double;
                      if (!(isnand (arg) || arg + arg == arg))
                        {
                          /* arg is finite and nonzero.  */
                          int exponent = floorlog10 (arg < 0 ? -arg : arg);
                          if (exponent >= 0 && tmp_length < exponent + precision)
                            tmp_length = exponent + precision;
                        }
                    }
