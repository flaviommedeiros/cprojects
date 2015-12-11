if (j1 == 0 && mode != 1 && !(word1(&u) & 1)
#ifdef Honor_FLT_ROUNDS
                && Rounding >= 1
#endif
                                   ) {
                if (dig == '9')
                    goto round_9_up;
                if (j > 0)
                    dig++;
#ifdef SET_INEXACT
                else if (!b->x[0] && b->wds <= 1)
                    inexact = 0;
#endif
                *s++ = dig;
                goto ret;
                }
