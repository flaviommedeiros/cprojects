if (bc.dsign || word1(&rv) || word0(&rv) & Bndry_mask
#ifdef IEEE_Arith /*{*/
#ifdef Avoid_Underflow
			 || (word0(&rv) & Exp_mask) <= (2*P+1)*Exp_msk1
#else
			 || (word0(&rv) & Exp_mask) <= Exp_msk1
#endif
#endif /*}*/
				) {
#ifdef SET_INEXACT
				if (!delta->x[0] && delta->wds <= 1)
					bc.inexact = 0;
#endif
				break;
				}
