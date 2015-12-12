#ifndef No_leftright
if (leftright) {
            /* Use Steele & White method of only
             * generating digits needed.
             */
            eps = 0.5/tens[ilim-1] - eps;
            for(i = 0;;) {
                L = (Long)d;
                d -= L;
                *s++ = '0' + (char)L;
                if (d < eps)
                    goto ret1;
                if (1. - d < eps)
                    goto bump_up;
                if (++i >= ilim)
                    break;
                eps *= 10.;
                d *= 10.;
            }
        }
        else {
#endif
            /* Generate ilim digits, then fix them up. */
            eps *= tens[ilim-1];
            for(i = 1;; i++, d *= 10.) {
                L = (Long)d;
                d -= L;
                *s++ = '0' + (char)L;
                if (i == ilim) {
                    if (d > 0.5 + eps)
                        goto bump_up;
                    else if (d < 0.5 - eps) {
                        while(*--s == '0') ;
                        s++;
                        goto ret1;
                    }
                    break;
                }
            }
#ifndef No_leftright
        }
