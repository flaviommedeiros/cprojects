# if NEED_PRINTF_LONG_DOUBLE || NEED_PRINTF_INFINITE_LONG_DOUBLE
if (type == TYPE_LONGDOUBLE)
#  endif
                  {
                    long double arg = a.arg[dp->arg_index].a.a_longdouble;

                    if (isnanl (arg))
                      {
                        if (dp->conversion >= 'A' && dp->conversion <= 'Z')
                          {
                            *p++ = 'N'; *p++ = 'A'; *p++ = 'N';
                          }
                        else
                          {
                            *p++ = 'n'; *p++ = 'a'; *p++ = 'n';
                          }
                      }
                    else
                      {
                        int sign = 0;
                        DECL_LONG_DOUBLE_ROUNDING

                        BEGIN_LONG_DOUBLE_ROUNDING ();

                        if (signbit (arg)) /* arg < 0.0L or negative zero */
                          {
                            sign = -1;
                            arg = -arg;
                          }

                        if (sign < 0)
                          *p++ = '-';
                        else if (flags & FLAG_SHOWSIGN)
                          *p++ = '+';
                        else if (flags & FLAG_SPACE)
                          *p++ = ' ';

                        if (arg > 0.0L && arg + arg == arg)
                          {
                            if (dp->conversion >= 'A' && dp->conversion <= 'Z')
                              {
                                *p++ = 'I'; *p++ = 'N'; *p++ = 'F';
                              }
                            else
                              {
                                *p++ = 'i'; *p++ = 'n'; *p++ = 'f';
                              }
                          }
                        else
                          {
#  if NEED_PRINTF_LONG_DOUBLE
                            pad_ptr = p;

                            if (dp->conversion == 'f' || dp->conversion == 'F')
                              {
                                char *digits;
                                size_t ndigits;

                                digits =
                                  scale10_round_decimal_long_double (arg, precision);
                                if (digits == NULL)
                                  {
                                    END_LONG_DOUBLE_ROUNDING ();
                                    goto out_of_memory;
                                  }
                                ndigits = strlen (digits);

                                if (ndigits > precision)
                                  do
                                    {
                                      --ndigits;
                                      *p++ = digits[ndigits];
                                    }
                                  while (ndigits > precision);
                                else
                                  *p++ = '0';
                                /* Here ndigits <= precision.  */
                                if ((flags & FLAG_ALT) || precision > 0)
                                  {
                                    *p++ = decimal_point_char ();
                                    for (; precision > ndigits; precision--)
                                      *p++ = '0';
                                    while (ndigits > 0)
                                      {
                                        --ndigits;
                                        *p++ = digits[ndigits];
                                      }
                                  }

                                free (digits);
                              }
                            else if (dp->conversion == 'e' || dp->conversion == 'E')
                              {
                                int exponent;

                                if (arg == 0.0L)
                                  {
                                    exponent = 0;
                                    *p++ = '0';
                                    if ((flags & FLAG_ALT) || precision > 0)
                                      {
                                        *p++ = decimal_point_char ();
                                        for (; precision > 0; precision--)
                                          *p++ = '0';
                                      }
                                  }
                                else
                                  {
                                    /* arg > 0.0L.  */
                                    int adjusted;
                                    char *digits;
                                    size_t ndigits;

                                    exponent = floorlog10l (arg);
                                    adjusted = 0;
                                    for (;;)
                                      {
                                        digits =
                                          scale10_round_decimal_long_double (arg,
                                                                             (int)precision - exponent);
                                        if (digits == NULL)
                                          {
                                            END_LONG_DOUBLE_ROUNDING ();
                                            goto out_of_memory;
                                          }
                                        ndigits = strlen (digits);

                                        if (ndigits == precision + 1)
                                          break;
                                        if (ndigits < precision
                                            || ndigits > precision + 2)
                                          /* The exponent was not guessed
                                             precisely enough.  */
                                          abort ();
                                        if (adjusted)
                                          /* None of two values of exponent is
                                             the right one.  Prevent an endless
                                             loop.  */
                                          abort ();
                                        free (digits);
                                        if (ndigits == precision)
                                          exponent -= 1;
                                        else
                                          exponent += 1;
                                        adjusted = 1;
                                      }
                                    /* Here ndigits = precision+1.  */
                                    if (is_borderline (digits, precision))
                                      {
                                        /* Maybe the exponent guess was too high
                                           and a smaller exponent can be reached
                                           by turning a 10...0 into 9...9x.  */
                                        char *digits2 =
                                          scale10_round_decimal_long_double (arg,
                                                                             (int)precision - exponent + 1);
                                        if (digits2 == NULL)
                                          {
                                            free (digits);
                                            END_LONG_DOUBLE_ROUNDING ();
                                            goto out_of_memory;
                                          }
                                        if (strlen (digits2) == precision + 1)
                                          {
                                            free (digits);
                                            digits = digits2;
                                            exponent -= 1;
                                          }
                                        else
                                          free (digits2);
                                      }
                                    /* Here ndigits = precision+1.  */

                                    *p++ = digits[--ndigits];
                                    if ((flags & FLAG_ALT) || precision > 0)
                                      {
                                        *p++ = decimal_point_char ();
                                        while (ndigits > 0)
                                          {
                                            --ndigits;
                                            *p++ = digits[ndigits];
                                          }
                                      }

                                    free (digits);
                                  }

                                *p++ = dp->conversion; /* 'e' or 'E' */
#   if WIDE_CHAR_VERSION
                                {
                                  static const wchar_t decimal_format[] =
                                    { '%', '+', '.', '2', 'd', '\0' };
                                  SNPRINTF (p, 6 + 1, decimal_format, exponent);
                                }
                                while (*p != '\0')
                                  p++;
#   else
                                if (sizeof (DCHAR_T) == 1)
                                  {
                                    sprintf ((char *) p, "%+.2d", exponent);
                                    while (*p != '\0')
                                      p++;
                                  }
                                else
                                  {
                                    char expbuf[6 + 1];
                                    const char *ep;
                                    sprintf (expbuf, "%+.2d", exponent);
                                    for (ep = expbuf; (*p = *ep) != '\0'; ep++)
                                      p++;
                                  }
#   endif
                              }
                            else if (dp->conversion == 'g' || dp->conversion == 'G')
                              {
                                if (precision == 0)
                                  precision = 1;
                                /* precision >= 1.  */

                                if (arg == 0.0L)
                                  /* The exponent is 0, >= -4, < precision.
                                     Use fixed-point notation.  */
                                  {
                                    size_t ndigits = precision;
                                    /* Number of trailing zeroes that have to be
                                       dropped.  */
                                    size_t nzeroes =
                                      (flags & FLAG_ALT ? 0 : precision - 1);

                                    --ndigits;
                                    *p++ = '0';
                                    if ((flags & FLAG_ALT) || ndigits > nzeroes)
                                      {
                                        *p++ = decimal_point_char ();
                                        while (ndigits > nzeroes)
                                          {
                                            --ndigits;
                                            *p++ = '0';
                                          }
                                      }
                                  }
                                else
                                  {
                                    /* arg > 0.0L.  */
                                    int exponent;
                                    int adjusted;
                                    char *digits;
                                    size_t ndigits;
                                    size_t nzeroes;

                                    exponent = floorlog10l (arg);
                                    adjusted = 0;
                                    for (;;)
                                      {
                                        digits =
                                          scale10_round_decimal_long_double (arg,
                                                                             (int)(precision - 1) - exponent);
                                        if (digits == NULL)
                                          {
                                            END_LONG_DOUBLE_ROUNDING ();
                                            goto out_of_memory;
                                          }
                                        ndigits = strlen (digits);

                                        if (ndigits == precision)
                                          break;
                                        if (ndigits < precision - 1
                                            || ndigits > precision + 1)
                                          /* The exponent was not guessed
                                             precisely enough.  */
                                          abort ();
                                        if (adjusted)
                                          /* None of two values of exponent is
                                             the right one.  Prevent an endless
                                             loop.  */
                                          abort ();
                                        free (digits);
                                        if (ndigits < precision)
                                          exponent -= 1;
                                        else
                                          exponent += 1;
                                        adjusted = 1;
                                      }
                                    /* Here ndigits = precision.  */
                                    if (is_borderline (digits, precision - 1))
                                      {
                                        /* Maybe the exponent guess was too high
                                           and a smaller exponent can be reached
                                           by turning a 10...0 into 9...9x.  */
                                        char *digits2 =
                                          scale10_round_decimal_long_double (arg,
                                                                             (int)(precision - 1) - exponent + 1);
                                        if (digits2 == NULL)
                                          {
                                            free (digits);
                                            END_LONG_DOUBLE_ROUNDING ();
                                            goto out_of_memory;
                                          }
                                        if (strlen (digits2) == precision)
                                          {
                                            free (digits);
                                            digits = digits2;
                                            exponent -= 1;
                                          }
                                        else
                                          free (digits2);
                                      }
                                    /* Here ndigits = precision.  */

                                    /* Determine the number of trailing zeroes
                                       that have to be dropped.  */
                                    nzeroes = 0;
                                    if ((flags & FLAG_ALT) == 0)
                                      while (nzeroes < ndigits
                                             && digits[nzeroes] == '0')
                                        nzeroes++;

                                    /* The exponent is now determined.  */
                                    if (exponent >= -4
                                        && exponent < (long)precision)
                                      {
                                        /* Fixed-point notation:
                                           max(exponent,0)+1 digits, then the
                                           decimal point, then the remaining
                                           digits without trailing zeroes.  */
                                        if (exponent >= 0)
                                          {
                                            size_t count = exponent + 1;
                                            /* Note: count <= precision = ndigits.  */
                                            for (; count > 0; count--)
                                              *p++ = digits[--ndigits];
                                            if ((flags & FLAG_ALT) || ndigits > nzeroes)
                                              {
                                                *p++ = decimal_point_char ();
                                                while (ndigits > nzeroes)
                                                  {
                                                    --ndigits;
                                                    *p++ = digits[ndigits];
                                                  }
                                              }
                                          }
                                        else
                                          {
                                            size_t count = -exponent - 1;
                                            *p++ = '0';
                                            *p++ = decimal_point_char ();
                                            for (; count > 0; count--)
                                              *p++ = '0';
                                            while (ndigits > nzeroes)
                                              {
                                                --ndigits;
                                                *p++ = digits[ndigits];
                                              }
                                          }
                                      }
                                    else
                                      {
                                        /* Exponential notation.  */
                                        *p++ = digits[--ndigits];
                                        if ((flags & FLAG_ALT) || ndigits > nzeroes)
                                          {
                                            *p++ = decimal_point_char ();
                                            while (ndigits > nzeroes)
                                              {
                                                --ndigits;
                                                *p++ = digits[ndigits];
                                              }
                                          }
                                        *p++ = dp->conversion - 'G' + 'E'; /* 'e' or 'E' */
#   if WIDE_CHAR_VERSION
                                        {
                                          static const wchar_t decimal_format[] =
                                            { '%', '+', '.', '2', 'd', '\0' };
                                          SNPRINTF (p, 6 + 1, decimal_format, exponent);
                                        }
                                        while (*p != '\0')
                                          p++;
#   else
                                        if (sizeof (DCHAR_T) == 1)
                                          {
                                            sprintf ((char *) p, "%+.2d", exponent);
                                            while (*p != '\0')
                                              p++;
                                          }
                                        else
                                          {
                                            char expbuf[6 + 1];
                                            const char *ep;
                                            sprintf (expbuf, "%+.2d", exponent);
                                            for (ep = expbuf; (*p = *ep) != '\0'; ep++)
                                              p++;
                                          }
#   endif
                                      }

                                    free (digits);
                                  }
                              }
                            else
                              abort ();
#  else
                            /* arg is finite.  */
                            if (!(arg == 0.0L))
                              abort ();

                            pad_ptr = p;

                            if (dp->conversion == 'f' || dp->conversion == 'F')
                              {
                                *p++ = '0';
                                if ((flags & FLAG_ALT) || precision > 0)
                                  {
                                    *p++ = decimal_point_char ();
                                    for (; precision > 0; precision--)
                                      *p++ = '0';
                                  }
                              }
                            else if (dp->conversion == 'e' || dp->conversion == 'E')
                              {
                                *p++ = '0';
                                if ((flags & FLAG_ALT) || precision > 0)
                                  {
                                    *p++ = decimal_point_char ();
                                    for (; precision > 0; precision--)
                                      *p++ = '0';
                                  }
                                *p++ = dp->conversion; /* 'e' or 'E' */
                                *p++ = '+';
                                *p++ = '0';
                                *p++ = '0';
                              }
                            else if (dp->conversion == 'g' || dp->conversion == 'G')
                              {
                                *p++ = '0';
                                if (flags & FLAG_ALT)
                                  {
                                    size_t ndigits =
                                      (precision > 0 ? precision - 1 : 0);
                                    *p++ = decimal_point_char ();
                                    for (; ndigits > 0; --ndigits)
                                      *p++ = '0';
                                  }
                              }
                            else if (dp->conversion == 'a' || dp->conversion == 'A')
                              {
                                *p++ = '0';
                                *p++ = dp->conversion - 'A' + 'X';
                                pad_ptr = p;
                                *p++ = '0';
                                if ((flags & FLAG_ALT) || precision > 0)
                                  {
                                    *p++ = decimal_point_char ();
                                    for (; precision > 0; precision--)
                                      *p++ = '0';
                                  }
                                *p++ = dp->conversion - 'A' + 'P';
                                *p++ = '+';
                                *p++ = '0';
                              }
                            else
                              abort ();
#  endif
                          }

                        END_LONG_DOUBLE_ROUNDING ();
                      }
                  }
#  if NEED_PRINTF_DOUBLE || NEED_PRINTF_INFINITE_DOUBLE
                else
#  endif
# endif
# if NEED_PRINTF_DOUBLE || NEED_PRINTF_INFINITE_DOUBLE
                  {
                    double arg = a.arg[dp->arg_index].a.a_double;

                    if (isnand (arg))
                      {
                        if (dp->conversion >= 'A' && dp->conversion <= 'Z')
                          {
                            *p++ = 'N'; *p++ = 'A'; *p++ = 'N';
                          }
                        else
                          {
                            *p++ = 'n'; *p++ = 'a'; *p++ = 'n';
                          }
                      }
                    else
                      {
                        int sign = 0;

                        if (signbit (arg)) /* arg < 0.0 or negative zero */
                          {
                            sign = -1;
                            arg = -arg;
                          }

                        if (sign < 0)
                          *p++ = '-';
                        else if (flags & FLAG_SHOWSIGN)
                          *p++ = '+';
                        else if (flags & FLAG_SPACE)
                          *p++ = ' ';

                        if (arg > 0.0 && arg + arg == arg)
                          {
                            if (dp->conversion >= 'A' && dp->conversion <= 'Z')
                              {
                                *p++ = 'I'; *p++ = 'N'; *p++ = 'F';
                              }
                            else
                              {
                                *p++ = 'i'; *p++ = 'n'; *p++ = 'f';
                              }
                          }
                        else
                          {
#  if NEED_PRINTF_DOUBLE
                            pad_ptr = p;

                            if (dp->conversion == 'f' || dp->conversion == 'F')
                              {
                                char *digits;
                                size_t ndigits;

                                digits =
                                  scale10_round_decimal_double (arg, precision);
                                if (digits == NULL)
                                  goto out_of_memory;
                                ndigits = strlen (digits);

                                if (ndigits > precision)
                                  do
                                    {
                                      --ndigits;
                                      *p++ = digits[ndigits];
                                    }
                                  while (ndigits > precision);
                                else
                                  *p++ = '0';
                                /* Here ndigits <= precision.  */
                                if ((flags & FLAG_ALT) || precision > 0)
                                  {
                                    *p++ = decimal_point_char ();
                                    for (; precision > ndigits; precision--)
                                      *p++ = '0';
                                    while (ndigits > 0)
                                      {
                                        --ndigits;
                                        *p++ = digits[ndigits];
                                      }
                                  }

                                free (digits);
                              }
                            else if (dp->conversion == 'e' || dp->conversion == 'E')
                              {
                                int exponent;

                                if (arg == 0.0)
                                  {
                                    exponent = 0;
                                    *p++ = '0';
                                    if ((flags & FLAG_ALT) || precision > 0)
                                      {
                                        *p++ = decimal_point_char ();
                                        for (; precision > 0; precision--)
                                          *p++ = '0';
                                      }
                                  }
                                else
                                  {
                                    /* arg > 0.0.  */
                                    int adjusted;
                                    char *digits;
                                    size_t ndigits;

                                    exponent = floorlog10 (arg);
                                    adjusted = 0;
                                    for (;;)
                                      {
                                        digits =
                                          scale10_round_decimal_double (arg,
                                                                        (int)precision - exponent);
                                        if (digits == NULL)
                                          goto out_of_memory;
                                        ndigits = strlen (digits);

                                        if (ndigits == precision + 1)
                                          break;
                                        if (ndigits < precision
                                            || ndigits > precision + 2)
                                          /* The exponent was not guessed
                                             precisely enough.  */
                                          abort ();
                                        if (adjusted)
                                          /* None of two values of exponent is
                                             the right one.  Prevent an endless
                                             loop.  */
                                          abort ();
                                        free (digits);
                                        if (ndigits == precision)
                                          exponent -= 1;
                                        else
                                          exponent += 1;
                                        adjusted = 1;
                                      }
                                    /* Here ndigits = precision+1.  */
                                    if (is_borderline (digits, precision))
                                      {
                                        /* Maybe the exponent guess was too high
                                           and a smaller exponent can be reached
                                           by turning a 10...0 into 9...9x.  */
                                        char *digits2 =
                                          scale10_round_decimal_double (arg,
                                                                        (int)precision - exponent + 1);
                                        if (digits2 == NULL)
                                          {
                                            free (digits);
                                            goto out_of_memory;
                                          }
                                        if (strlen (digits2) == precision + 1)
                                          {
                                            free (digits);
                                            digits = digits2;
                                            exponent -= 1;
                                          }
                                        else
                                          free (digits2);
                                      }
                                    /* Here ndigits = precision+1.  */

                                    *p++ = digits[--ndigits];
                                    if ((flags & FLAG_ALT) || precision > 0)
                                      {
                                        *p++ = decimal_point_char ();
                                        while (ndigits > 0)
                                          {
                                            --ndigits;
                                            *p++ = digits[ndigits];
                                          }
                                      }

                                    free (digits);
                                  }

                                *p++ = dp->conversion; /* 'e' or 'E' */
#   if WIDE_CHAR_VERSION
                                {
                                  static const wchar_t decimal_format[] =
                                    /* Produce the same number of exponent digits
                                       as the native printf implementation.  */
#    if (defined _WIN32 || defined __WIN32__) && ! defined __CYGWIN__
                                    { '%', '+', '.', '3', 'd', '\0' };
#    else
                                    { '%', '+', '.', '2', 'd', '\0' };
#    endif
                                  SNPRINTF (p, 6 + 1, decimal_format, exponent);
                                }
                                while (*p != '\0')
                                  p++;
#   else
                                {
                                  static const char decimal_format[] =
                                    /* Produce the same number of exponent digits
                                       as the native printf implementation.  */
#    if (defined _WIN32 || defined __WIN32__) && ! defined __CYGWIN__
                                    "%+.3d";
#    else
                                    "%+.2d";
#    endif
                                  if (sizeof (DCHAR_T) == 1)
                                    {
                                      sprintf ((char *) p, decimal_format, exponent);
                                      while (*p != '\0')
                                        p++;
                                    }
                                  else
                                    {
                                      char expbuf[6 + 1];
                                      const char *ep;
                                      sprintf (expbuf, decimal_format, exponent);
                                      for (ep = expbuf; (*p = *ep) != '\0'; ep++)
                                        p++;
                                    }
                                }
#   endif
                              }
                            else if (dp->conversion == 'g' || dp->conversion == 'G')
                              {
                                if (precision == 0)
                                  precision = 1;
                                /* precision >= 1.  */

                                if (arg == 0.0)
                                  /* The exponent is 0, >= -4, < precision.
                                     Use fixed-point notation.  */
                                  {
                                    size_t ndigits = precision;
                                    /* Number of trailing zeroes that have to be
                                       dropped.  */
                                    size_t nzeroes =
                                      (flags & FLAG_ALT ? 0 : precision - 1);

                                    --ndigits;
                                    *p++ = '0';
                                    if ((flags & FLAG_ALT) || ndigits > nzeroes)
                                      {
                                        *p++ = decimal_point_char ();
                                        while (ndigits > nzeroes)
                                          {
                                            --ndigits;
                                            *p++ = '0';
                                          }
                                      }
                                  }
                                else
                                  {
                                    /* arg > 0.0.  */
                                    int exponent;
                                    int adjusted;
                                    char *digits;
                                    size_t ndigits;
                                    size_t nzeroes;

                                    exponent = floorlog10 (arg);
                                    adjusted = 0;
                                    for (;;)
                                      {
                                        digits =
                                          scale10_round_decimal_double (arg,
                                                                        (int)(precision - 1) - exponent);
                                        if (digits == NULL)
                                          goto out_of_memory;
                                        ndigits = strlen (digits);

                                        if (ndigits == precision)
                                          break;
                                        if (ndigits < precision - 1
                                            || ndigits > precision + 1)
                                          /* The exponent was not guessed
                                             precisely enough.  */
                                          abort ();
                                        if (adjusted)
                                          /* None of two values of exponent is
                                             the right one.  Prevent an endless
                                             loop.  */
                                          abort ();
                                        free (digits);
                                        if (ndigits < precision)
                                          exponent -= 1;
                                        else
                                          exponent += 1;
                                        adjusted = 1;
                                      }
                                    /* Here ndigits = precision.  */
                                    if (is_borderline (digits, precision - 1))
                                      {
                                        /* Maybe the exponent guess was too high
                                           and a smaller exponent can be reached
                                           by turning a 10...0 into 9...9x.  */
                                        char *digits2 =
                                          scale10_round_decimal_double (arg,
                                                                        (int)(precision - 1) - exponent + 1);
                                        if (digits2 == NULL)
                                          {
                                            free (digits);
                                            goto out_of_memory;
                                          }
                                        if (strlen (digits2) == precision)
                                          {
                                            free (digits);
                                            digits = digits2;
                                            exponent -= 1;
                                          }
                                        else
                                          free (digits2);
                                      }
                                    /* Here ndigits = precision.  */

                                    /* Determine the number of trailing zeroes
                                       that have to be dropped.  */
                                    nzeroes = 0;
                                    if ((flags & FLAG_ALT) == 0)
                                      while (nzeroes < ndigits
                                             && digits[nzeroes] == '0')
                                        nzeroes++;

                                    /* The exponent is now determined.  */
                                    if (exponent >= -4
                                        && exponent < (long)precision)
                                      {
                                        /* Fixed-point notation:
                                           max(exponent,0)+1 digits, then the
                                           decimal point, then the remaining
                                           digits without trailing zeroes.  */
                                        if (exponent >= 0)
                                          {
                                            size_t count = exponent + 1;
                                            /* Note: count <= precision = ndigits.  */
                                            for (; count > 0; count--)
                                              *p++ = digits[--ndigits];
                                            if ((flags & FLAG_ALT) || ndigits > nzeroes)
                                              {
                                                *p++ = decimal_point_char ();
                                                while (ndigits > nzeroes)
                                                  {
                                                    --ndigits;
                                                    *p++ = digits[ndigits];
                                                  }
                                              }
                                          }
                                        else
                                          {
                                            size_t count = -exponent - 1;
                                            *p++ = '0';
                                            *p++ = decimal_point_char ();
                                            for (; count > 0; count--)
                                              *p++ = '0';
                                            while (ndigits > nzeroes)
                                              {
                                                --ndigits;
                                                *p++ = digits[ndigits];
                                              }
                                          }
                                      }
                                    else
                                      {
                                        /* Exponential notation.  */
                                        *p++ = digits[--ndigits];
                                        if ((flags & FLAG_ALT) || ndigits > nzeroes)
                                          {
                                            *p++ = decimal_point_char ();
                                            while (ndigits > nzeroes)
                                              {
                                                --ndigits;
                                                *p++ = digits[ndigits];
                                              }
                                          }
                                        *p++ = dp->conversion - 'G' + 'E'; /* 'e' or 'E' */
#   if WIDE_CHAR_VERSION
                                        {
                                          static const wchar_t decimal_format[] =
                                            /* Produce the same number of exponent digits
                                               as the native printf implementation.  */
#    if (defined _WIN32 || defined __WIN32__) && ! defined __CYGWIN__
                                            { '%', '+', '.', '3', 'd', '\0' };
#    else
                                            { '%', '+', '.', '2', 'd', '\0' };
#    endif
                                          SNPRINTF (p, 6 + 1, decimal_format, exponent);
                                        }
                                        while (*p != '\0')
                                          p++;
#   else
                                        {
                                          static const char decimal_format[] =
                                            /* Produce the same number of exponent digits
                                               as the native printf implementation.  */
#    if (defined _WIN32 || defined __WIN32__) && ! defined __CYGWIN__
                                            "%+.3d";
#    else
                                            "%+.2d";
#    endif
                                          if (sizeof (DCHAR_T) == 1)
                                            {
                                              sprintf ((char *) p, decimal_format, exponent);
                                              while (*p != '\0')
                                                p++;
                                            }
                                          else
                                            {
                                              char expbuf[6 + 1];
                                              const char *ep;
                                              sprintf (expbuf, decimal_format, exponent);
                                              for (ep = expbuf; (*p = *ep) != '\0'; ep++)
                                                p++;
                                            }
                                        }
#   endif
                                      }

                                    free (digits);
                                  }
                              }
                            else
                              abort ();
#  else
                            /* arg is finite.  */
                            if (!(arg == 0.0))
                              abort ();

                            pad_ptr = p;

                            if (dp->conversion == 'f' || dp->conversion == 'F')
                              {
                                *p++ = '0';
                                if ((flags & FLAG_ALT) || precision > 0)
                                  {
                                    *p++ = decimal_point_char ();
                                    for (; precision > 0; precision--)
                                      *p++ = '0';
                                  }
                              }
                            else if (dp->conversion == 'e' || dp->conversion == 'E')
                              {
                                *p++ = '0';
                                if ((flags & FLAG_ALT) || precision > 0)
                                  {
                                    *p++ = decimal_point_char ();
                                    for (; precision > 0; precision--)
                                      *p++ = '0';
                                  }
                                *p++ = dp->conversion; /* 'e' or 'E' */
                                *p++ = '+';
                                /* Produce the same number of exponent digits as
                                   the native printf implementation.  */
#   if (defined _WIN32 || defined __WIN32__) && ! defined __CYGWIN__
                                *p++ = '0';
#   endif
                                *p++ = '0';
                                *p++ = '0';
                              }
                            else if (dp->conversion == 'g' || dp->conversion == 'G')
                              {
                                *p++ = '0';
                                if (flags & FLAG_ALT)
                                  {
                                    size_t ndigits =
                                      (precision > 0 ? precision - 1 : 0);
                                    *p++ = decimal_point_char ();
                                    for (; ndigits > 0; --ndigits)
                                      *p++ = '0';
                                  }
                              }
                            else
                              abort ();
#  endif
                          }
                      }
                  }
