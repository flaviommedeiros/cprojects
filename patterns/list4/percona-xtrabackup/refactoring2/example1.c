#if QLZ_COMPRESSION_LEVEL == 3
if(((fast_read(o, 3) ^ fetch) & 0xffffff) == 0 && o < src - MINOFFSET)
#elif QLZ_COMPRESSION_LEVEL == 2
				if(*(src + matchlen) == *(o + matchlen)	&& ((fast_read(o, 3) ^ fetch) & 0xffffff) == 0 && o < src - MINOFFSET)
#endif
				{	
					m = 3;
					while(*(o + m) == *(src + m) && m < remaining)
						m++;
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
				}
