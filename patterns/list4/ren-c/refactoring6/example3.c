if ((word0(&rv) & Bndry_mask1) == Bndry_mask1
                 &&  word1(&rv) == (
#ifdef Avoid_Underflow
            (bc.scale && (y = word0(&rv) & Exp_mask) <= 2*P*Exp_msk1)
        ? (0xffffffff & (0xffffffff << (2*P+1-(y>>Exp_shift)))) :
#endif
                           0xffffffff)) {
                    /*boundary case -- increment exponent*/
                    if (word0(&rv) == Big0 && word1(&rv) == Big1)
                        goto ovfl;
                    word0(&rv) = (word0(&rv) & Exp_mask)
                        + Exp_msk1
#ifdef IBM
                        | Exp_msk1 >> 4
#endif
                        ;
                    word1(&rv) = 0;
#ifdef Avoid_Underflow
                    bc.dsign = 0;
#endif
                    break;
                    }
