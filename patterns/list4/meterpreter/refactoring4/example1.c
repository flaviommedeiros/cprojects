#ifdef Sudden_Underflow
if (L <  Exp_msk1)
#else
				if (L <= Exp_msk1)
#endif
					goto undfl;
