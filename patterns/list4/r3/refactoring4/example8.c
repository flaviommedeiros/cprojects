#ifdef ROUND_BIASED
if (dval(&u) >= ds)
#else
				if (dval(&u) > ds || (dval(&u) == ds && L & 1))
#endif
					{
 bump_up:
					while(*--s == '9')
						if (s == s0) {
							k++;
							*s = '0';
							break;
							}
					++*s++;
					}
