if (!word1(d) && !(word0(d) & Bndry_mask)
#ifndef Sudden_Underflow
                && word0(d) & (Exp_mask & Exp_mask << 1)
#endif
                ) {
                /* The special case.  Here we want to be within a quarter of the last input
                   significant digit instead of one half of it when the output string's value is less than d.  */
                s2 += Log2P;
                mhi = i2b(1<<Log2P);
                if (!mhi)
                    goto nomem2;
            }
