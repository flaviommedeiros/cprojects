if (!word1(&u) && !(word0(&u) & Bndry_mask)
#ifndef Sudden_Underflow
         && word0(&u) & (Exp_mask & ~Exp_msk1)
#endif
                ) {
            /* The special case */
            b2 += Log2P;
            s2 += Log2P;
            spec_case = 1;
            }
