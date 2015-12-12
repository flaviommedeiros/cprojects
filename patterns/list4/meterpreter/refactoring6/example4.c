if (j < 0 || (j == 0 && !mode
#ifndef ROUND_BIASED
							&& !(word1(d) & 1)
#endif
					)) {
				if (jj1 > 0) {
					b = lshift(b, 1);
					jj1 = cmp(b, S);
					if ((jj1 > 0 || (jj1 == 0 && dig & 1))
					&& dig++ == '9')
						goto round_9_up;
					}
				*s++ = dig;
				goto ret;
			}
