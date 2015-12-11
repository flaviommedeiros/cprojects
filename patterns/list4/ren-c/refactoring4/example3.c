#ifdef Sudden_Underflow
if (L <  Exp_msk1)
#else
#ifdef Avoid_Underflow
                if (L <= (bc.scale ? (2*P+1)*Exp_msk1 : Exp_msk1))
#else
                if (L <= Exp_msk1)
#endif /*Avoid_Underflow*/
#endif /*IBM*/
                    {
                    if (bc.nd >nd) {
                        bc.uflchk = 1;
                        break;
                        }
                    goto undfl;
                    }
