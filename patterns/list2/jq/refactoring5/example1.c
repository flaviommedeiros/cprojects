#ifndef Sudden_Underflow
if (de) {
#endif
#ifdef IBM
		*e = (de - Bias - (P-1) << 2) + k;
		*bits = 4*P + 8 - k - hi0bits(C, word0(d) & Frac_mask);
#else
		*e = de - Bias - (P-1) + k;
		*bits = P - k;
#endif
#ifndef Sudden_Underflow
		}
	else {
		*e = de - Bias - (P-1) + 1 + k;
#ifdef Pack_32
		*bits = 32*i - hi0bits(C, x[i-1]);
#else
		*bits = (i+2)*16 - hi0bits(C, x[i]);
#endif
		}
