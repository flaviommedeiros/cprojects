#if defined(IEEE_Arith) + defined(VAX)
if ((word0(&u) & Exp_mask) == Exp_mask)
#else
	if (word0(&u)  == 0x8000)
#endif
		{
		/* Infinity or NaN */
		*decpt = 9999;
#ifdef IEEE_Arith
		if (!word1(&u) && !(word0(&u) & 0xfffff))
			return nrv_alloc(C, "Infinity", rve, 8);
#endif
		return nrv_alloc(C, "NaN", rve, 3);
		}
