#ifndef ROUND_BIASED
if (j1 == 0 && !(word1(d) & 1)) {
                    if (j > 0)
                        digit++;
                    done = JS_TRUE;
                } else
#endif
                if (j < 0 || (j == 0
#ifndef ROUND_BIASED
                    && !(word1(d) & 1)
#endif
                    )) {
                    if (j1 > 0) {
                        /* Either dig or dig+1 would work here as the least significant digit.
                           Use whichever would produce an output value closer to d. */
                        b = lshift(b, 1);
                        if (!b)
                            goto nomem2;
                        j1 = cmp(b, s);
                        if (j1 > 0) /* The even test (|| (j1 == 0 && (digit & 1))) is not here because it messes up odd base output
                                     * such as 3.5 in base 3.  */
                            digit++;
                    }
                    done = JS_TRUE;
                } else if (j1 > 0) {
                    digit++;
                    done = JS_TRUE;
                }
