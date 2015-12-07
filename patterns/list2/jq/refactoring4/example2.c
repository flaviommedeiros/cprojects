#ifdef Avoid_Underflow
if (!bc.scale || y > 2*P*Exp_msk1)
#else
						if (y)
#endif
						  {
						  delta = lshift(C, delta,Log2P);
						  if (cmp(C, delta, bs) <= 0)
							adj.d = -0.5;
						  }
