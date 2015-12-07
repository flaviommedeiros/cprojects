#if defined(LZO_UNALIGNED_OK_4) || defined(LZO_ALIGNED_OK_4)
if (PTR_ALIGNED2_4(op, ip))
# endif
		{
			COPY4(op, ip);
			op += 4;
			ip += 4;
			if (--t > 0) {
				if (t >= 4) {
					do {
						COPY4(op, ip);
						op += 4;
						ip += 4;
						t -= 4;
					} while (t >= 4);
					if (t > 0)
						do *op++ = *ip++; while (--t > 0);
				} else {
					do *op++ = *ip++; while (--t > 0);
				}
			}
		}
# if !defined(LZO_UNALIGNED_OK_4)
		else
# endif
#endif
#if !defined(LZO_UNALIGNED_OK_4)
		{
			*op++ = *ip++;
			*op++ = *ip++;
			*op++ = *ip++;
			do *op++ = *ip++; while (--t > 0);
		}
