#if QLZ_COMPRESSION_LEVEL == 3
if ((m > matchlen) || (m == matchlen && o > offset2))
#elif QLZ_COMPRESSION_LEVEL == 2
					if (m > matchlen)
#endif
					{
						offset2 = o;
						matchlen = m;
						best_k = k;
					}
