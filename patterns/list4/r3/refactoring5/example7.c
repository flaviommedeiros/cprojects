#ifdef Sudden_Underflow
if ((word0(&rv) & Exp_mask) <=
							P*Exp_msk1) {
						word0(&rv) += P*Exp_msk1;
						dval(&rv) += adj.d*ulp(dval(&rv));
						word0(&rv) -= P*Exp_msk1;
						}
					else
#endif /*Sudden_Underflow*/
#endif /*Avoid_Underflow}*/
					dval(&rv) += adj.d*ulp(&rv);
