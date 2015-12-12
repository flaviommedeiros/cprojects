if (nd <= DBL_DIG
#ifndef RND_PRODQUOT
        && FLT_ROUNDS == 1
#endif
        ) {
        if (!e)
            goto ret;
        if (e > 0) {
            if (e <= Ten_pmax) {
                /* rv = */ rounded_product(rv, tens[e]);
                goto ret;
            }
            i = DBL_DIG - nd;
            if (e <= Ten_pmax + i) {
                /* A fancier test would sometimes let us do
                 * this for larger i values.
                 */
                e -= i;
                rv *= tens[i];
                /* rv = */ rounded_product(rv, tens[e]);
                goto ret;
            }
        }
#ifndef Inaccurate_Divide
        else if (e >= -Ten_pmax) {
            /* rv = */ rounded_quotient(rv, tens[-e]);
            goto ret;
        }
#endif
    }
