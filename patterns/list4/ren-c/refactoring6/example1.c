if (nd <= DBL_DIG
#ifndef RND_PRODQUOT
#ifndef Honor_FLT_ROUNDS
        && Flt_Rounds == 1
#endif
#endif
            ) {
        if (!e)
            goto ret;
#ifndef ROUND_BIASED_without_Round_Up
        if (e > 0) {
            if (e <= Ten_pmax) {
#ifdef VAX
                goto vax_ovfl_check;
#else
#ifdef Honor_FLT_ROUNDS
                /* round correctly FLT_ROUNDS = 2 or 3 */
                if (sign) {
                    rv.d = -rv.d;
                    sign = 0;
                    }
#endif
                /* rv = */ rounded_product(dval(&rv), tens[e]);
                goto ret;
#endif
                }
            i = DBL_DIG - nd;
            if (e <= Ten_pmax + i) {
                /* A fancier test would sometimes let us do
                 * this for larger i values.
                 */
#ifdef Honor_FLT_ROUNDS
                /* round correctly FLT_ROUNDS = 2 or 3 */
                if (sign) {
                    rv.d = -rv.d;
                    sign = 0;
                    }
#endif
                e -= i;
                dval(&rv) *= tens[i];
#ifdef VAX
                /* VAX exponent range is so narrow we must
                 * worry about overflow here...
                 */
 vax_ovfl_check:
                word0(&rv) -= P*Exp_msk1;
                /* rv = */ rounded_product(dval(&rv), tens[e]);
                if ((word0(&rv) & Exp_mask)
                 > Exp_msk1*(DBL_MAX_EXP+Bias-1-P))
                    goto ovfl;
                word0(&rv) += P*Exp_msk1;
#else
                /* rv = */ rounded_product(dval(&rv), tens[e]);
#endif
                goto ret;
                }
            }
#ifndef Inaccurate_Divide
        else if (e >= -Ten_pmax) {
#ifdef Honor_FLT_ROUNDS
            /* round correctly FLT_ROUNDS = 2 or 3 */
            if (sign) {
                rv.d = -rv.d;
                sign = 0;
                }
#endif
            /* rv = */ rounded_quotient(dval(&rv), tens[-e]);
            goto ret;
            }
#endif
#endif /* ROUND_BIASED_without_Round_Up */
        }
