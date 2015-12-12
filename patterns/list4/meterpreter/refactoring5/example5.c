#ifndef No_leftright
if (leftright) {
			/* Use Steele & White method of only
			 * generating digits needed.
			 */
			value(eps) = 0.5/tens[ilim-1] - value(eps);
			for(i = 0;;) {
				L = value(d);
				value(d) -= L;
				*s++ = '0' + (int)L;
				if (value(d) < value(eps))
					goto ret1;
				if (1. - value(d) < value(eps))
					goto bump_up;
				if (++i >= ilim)
					break;
				value(eps) *= 10.;
				value(d) *= 10.;
				}
		}
		else {
#endif
			/* Generate ilim digits, then fix them up. */
			value(eps) *= tens[ilim-1];
			for(i = 1;; i++, value(d) *= 10.) {
				L = value(d);
				value(d) -= L;
				*s++ = '0' + (int)L;
				if (i == ilim) {
					if (value(d) > 0.5 + value(eps))
						goto bump_up;
					else if (value(d) < 0.5 - value(eps)) {
						while(*--s == '0');
						s++;
						goto ret1;
						}
					break;
				}
			}
#ifndef No_leftright
		}
