#if defined(IEEE_Arith) + defined(VAX)
if ((word0 (d) & Exp_mask) == Exp_mask)
#else
  if (word0 (d) == 0x8000)
#endif
    {
      /* Infinity or NaN */
      *decpt = 9999;
      s =
#ifdef IEEE_Arith
	!word1 (d) && !(word0 (d) & 0xfffff) ? "Infinity" :
#endif
	"NaN";
      if (rve)
	*rve =
#ifdef IEEE_Arith
	  s[3] ? s + 8 :
#endif
	  s + 3;


      return s;
    }
