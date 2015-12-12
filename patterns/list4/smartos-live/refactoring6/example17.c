if ((j < 0) || (j == 0 && !mode
#ifndef ROUND_BIASED
                && !(word1(d) & 1)
#endif
                )) {
                if (j1 > 0) {
                    /* Either dig or dig+1 would work here as the least significant decimal digit.
                       Use whichever would produce a decimal value closer to d. */
                    b = lshift(b, 1);
                    if (!b)
                        goto nomem;
                    j1 = cmp(b, S);
                    if (((j1 > 0) || (j1 == 0 && (dig & 1 || biasUp)))
                        && (dig++ == '9'))
                        goto round_9_up;
                }
                *s++ = (char)dig;
                goto ret;
            }
