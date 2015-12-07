#ifndef SET_INEXACT
if (bc.nd == nd) {
#ifdef Avoid_Underflow
		if (!bc.scale)
#endif
		if (y == z) {
			/* Can we stop now? */
			L = (Long)aadj;
			aadj -= L;
			/* The tolerances below are conservative. */
			if (bc.dsign || word1(&rv) || word0(&rv) & Bndry_mask) {
				if (aadj < .4999999 || aadj > .5000001)
					break;
				}
			else if (aadj < .4999999/FLT_RADIX)
				break;
			}
		}
