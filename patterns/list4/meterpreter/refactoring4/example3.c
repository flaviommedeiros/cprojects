#if defined(IEEE_Arith) + defined(VAX)
if ((word0(d) & Exp_mask) == Exp_mask)
#else
	if (word0(d)  == 0x8000)
#endif
	{
		/* Infinity or NaN */
		*decpt = 9999;
		s =
#ifdef IEEE_Arith
			!word1(d) && !(word0(d) & 0xfffff) ? "Infinity" :
#endif
				"NaN";
		result = Balloc(strlen(s)+1);
		if (result == BIGINT_INVALID)
			return NULL;
		s0 = (char *)(void *)result;
		strcpy(s0, s);
		if (rve)
			*rve =
#ifdef IEEE_Arith
				s0[3] ? s0 + 8 :
#endif
				s0 + 3;
		return s0;
	}
