#ifndef SMALL_SCANF
if ((aadj = ratio (delta, bs)) <= 2.)
	{
	#else
	 if ((aadj = small_ratio (delta, bs)) <= 2.)
	{
	#endif
	  if (dsign)
	    aadj = aadj1 = 1.;
	  else if (word1 (rv) || word0 (rv) & Bndry_mask)
	    {
#ifndef Sudden_Underflow
	      if (word1 (rv) == Tiny1 && !word0 (rv))
		goto undfl;
#endif
	      aadj = 1.;
	      aadj1 = -1.;
	    }
	  else
	    {
	      /* special case -- power of FLT_RADIX to be */
	      /* rounded down... */

	      if (aadj < 2. / FLT_RADIX)
		aadj = 1. / FLT_RADIX;
	      else
		aadj *= 0.5;
	      aadj1 = -aadj;
	    }
	}
      else
	{
	  aadj *= 0.5;
	  aadj1 = dsign ? aadj : -aadj;
#ifdef Check_FLT_ROUNDS
	  switch (FLT_ROUNDS)
	    {
	    case 2:		/* towards +infinity */
	      aadj1 -= 0.5;
	      break;
	    case 0:		/* towards 0 */
	    case 3:		/* towards -infinity */
	      aadj1 += 0.5;
	    }
#else
	  if (FLT_ROUNDS == 0)
	    aadj1 += 0.5;
#endif
	}
      y = word0 (rv) & Exp_mask;

      /* Check for overflow */

      if (y == Exp_msk1 * (DBL_MAX_EXP + Bias - 1))
	{
	  rv0.d = rv.d;
	  word0 (rv) -= P * Exp_msk1;
	  #ifndef SMALL_SCANF
	  adj = aadj1 * ulp (rv.d);
	  #else
	  adj = aadj1 * small_ulp (rv.d);
	  #endif
	  rv.d += adj;
	  if ((word0 (rv) & Exp_mask) >=
	      Exp_msk1 * (DBL_MAX_EXP + Bias - P))
	    {
	      if (word0 (rv0) == Big0 && word1 (rv0) == Big1)
		goto ovfl;
#ifdef _DOUBLE_IS_32BITS
	      word0 (rv) = Big1;
#else
	      word0 (rv) = Big0;
	      word1 (rv) = Big1;
#endif
	      goto cont;
	    }
	  else
	    word0 (rv) += P * Exp_msk1;
	}
      else
	{
#ifdef Sudden_Underflow
	  if ((word0 (rv) & Exp_mask) <= P * Exp_msk1)
	    {
	      rv0.d = rv.d;
	      word0 (rv) += P * Exp_msk1;
	      #ifndef SMALL_SCANF
	  		adj = aadj1 * ulp (rv.d);
	  		#else
	  		adj = aadj1 * small_ulp (rv.d);
	  		#endif
	      rv.d += adj;
	#ifdef IBM
	      if ((word0 (rv) & Exp_mask) < P * Exp_msk1)
	#else
	      if ((word0 (rv) & Exp_mask) <= P * Exp_msk1)
	#endif
		{
		  if (word0 (rv0) == Tiny0
		      && word1 (rv0) == Tiny1)
		    goto undfl;
		  word0 (rv) = Tiny0;
		  word1 (rv) = Tiny1;
		  goto cont;
		}
	      else
		word0 (rv) -= P * Exp_msk1;
	    }
	  else
	    {
	      #ifndef SMALL_SCANF
	 		adj = aadj1 * ulp (rv.d);
	  		#else
	  		adj = aadj1 * small_ulp (rv.d);
	 		#endif
	      rv.d += adj;
	    }
#else
	  /* Compute adj so that the IEEE rounding rules will
	   * correctly round rv.d + adj in some half-way cases.
	   * If rv.d * ulp(rv.d) is denormalized (i.e.,
	   * y <= (P-1)*Exp_msk1), we must adjust aadj to avoid
	   * trouble from bits lost to denormalization;
	   * example: 1.2e-307 .
	   */
	  if (y <= (P - 1) * Exp_msk1 && aadj >= 1.)
	    {
	      aadj1 = (double) (int) (aadj + 0.5);
	      if (!dsign)
		aadj1 = -aadj1;
	    }
	  #ifndef SMALL_SCANF
	  adj = aadj1 * ulp (rv.d);	  
	  #else
	  adj = aadj1 * small_ulp (rv.d);
	  rv.d += adj;
	  #endif
#endif
	}
      z = word0 (rv) & Exp_mask;
      if (y == z)
	{
	  /* Can we stop now? */
	  L = aadj;
	  aadj -= L;
	  /* The tolerances below are conservative. */
	  if (dsign || word1 (rv) || word0 (rv) & Bndry_mask)
	    {
	      if (aadj < .4999999 || aadj > .5000001)
		break;
	    }
	  else if (aadj < .4999999 / FLT_RADIX)
	    break;
	}
    cont:
     #ifndef SMALL_SCANF
      Bfree (ptr, bb);
      Bfree (ptr, bd);
      Bfree (ptr, bs);
      Bfree (ptr, delta);
     #else
     ;
     #endif
    }
