if (j < 0 || (j == 0 && mode != 1
#ifndef ROUND_BIASED
                            && !(word1(&u) & 1)
#endif
                    )) {
                if (!b->x[0] && b->wds <= 1) {
#ifdef SET_INEXACT
                    inexact = 0;
#endif
                    goto accept_dig;
                    }
#ifdef Honor_FLT_ROUNDS
                if (mode > 1)
                 switch(Rounding) {
                  case 0: goto accept_dig;
                  case 2: goto keep_dig;
                  }
#endif /*Honor_FLT_ROUNDS*/
                if (j1 > 0) {
                    b = lshift(b, 1);
                    j1 = cmp(b, S);
#ifdef ROUND_BIASED
                    if (j1 >= 0 /*)*/
#else
                    if ((j1 > 0 || (j1 == 0 && dig & 1))
#endif
                    && dig++ == '9')
                        goto round_9_up;
                    }
 accept_dig:
                *s++ = dig;
                goto ret;
                }
