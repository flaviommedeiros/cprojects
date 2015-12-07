#ifdef Honor_FLT_ROUNDS
if (bc->rounding != 1) {
		if (dd < 0) {
			if (bc->rounding == 0) {
				if (!dsign)
					goto retlow1;
				}
			else if (dsign)
				goto rethi1;
			}
		else if (dd > 0) {
			if (bc->rounding == 0) {
				if (dsign)
					goto rethi1;
				goto ret1;
				}
			if (!dsign)
				goto rethi1;
			dval(rv) += 2.*sulp(C, rv,bc);
			}
		else {
			bc->inexact = 0;
			if (dsign)
				goto rethi1;
			}
		}
	else
#endif
	if (speccase) {
		if (dd <= 0)
			rv->d = 0.;
		}
	else if (dd < 0) {
		if (!dsign)	/* does not happen for round-near */
retlow1:
			dval(rv) -= sulp(C, rv,bc);
		}
	else if (dd > 0) {
		if (dsign) {
 rethi1:
			dval(rv) += sulp(C, rv,bc);
			}
		}
	else {
		/* Exact half-way case:  apply round-even rule. */
		if ((j = ((word0(rv) & Exp_mask) >> Exp_shift) - bc->scale) <= 0) {
			i = 1 - j;
			if (i <= 31) {
				if (word1(rv) & (0x1 << i))
					goto odd;
				}
			else if (word0(rv) & (0x1 << (i-32)))
				goto odd;
			}
		else if (word1(rv) & 1) {
 odd:
			if (dsign)
				goto rethi1;
			goto retlow1;
			}
		}
