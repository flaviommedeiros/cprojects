if (dsign || word1(rv) || word0(rv) & Bndry_mask
#ifdef Avoid_Underflow
             || (word0(rv) & Exp_mask) <= Exp_msk1 + P*Exp_msk1
#else
             || (word0(rv) & Exp_mask) <= Exp_msk1
#endif
                ) {
#ifdef Avoid_Underflow
                if (!delta->x[0] && delta->wds == 1)
                    dsign = 2;
#endif
                break;
                }
