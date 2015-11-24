if (nd <= DBL_DIG
#ifndef RND_PRODQUOT
      && FLT_ROUNDS == 1
#endif
    )
    {
      if (!e)
	goto ret;
      if (e > 0)
	{
	  if (e <= Ten_pmax)
	    {
#ifdef VAX
	      goto vax_ovfl_check;
#else
	      #ifndef SMALL_SCANF
	      /* rv.d = */ rounded_product (rv.d, tens[e]);
	      #else
	      rounded_product (rv.d, small_tens[e]);
	      #endif
	      goto ret;
#endif
	    }
	  i = DBL_DIG - nd;
	  if (e <= Ten_pmax + i)
	    {
	      /* A fancier test would sometimes let us do
				 * this for larger i values.
				 */
	      e -= i;
	      #ifndef SMALL_SCANF
	      rv.d *= tens[i];
	      #else
	      rv.d *= small_tens[i];
	      #endif
#ifdef VAX
	      /* VAX exponent range is so narrow we must
	       * worry about overflow here...
	       */
	    vax_ovfl_check:
	      word0 (rv) -= P * Exp_msk1;
	       #ifndef SMALL_SCANF
	      /* rv.d = */ rounded_product (rv.d, tens[e]);
	      #else 
	      /* rv.d = */ rounded_product (rv.d, small_tens[e]);
	      #endif
	      if ((word0 (rv) & Exp_mask)
		  > Exp_msk1 * (DBL_MAX_EXP + Bias - 1 - P))
		goto ovfl;
	      word0 (rv) += P * Exp_msk1;
#else
	       #ifndef SMALL_SCANF
	      /* rv.d = */ rounded_product (rv.d, tens[e]);
	      #else 
	      /* rv.d = */ rounded_product (rv.d, small_tens[e]);
	      #endif
#endif
	      goto ret;
	    }
	}
#ifndef Inaccurate_Divide
      else if (e >= -Ten_pmax)
	{
	  #ifndef SMALL_SCANF
	  /* rv.d = */ rounded_quotient (rv.d, tens[-e]);
	  #else
	  /* rv.d = */ rounded_quotient (rv.d, small_tens[-e]);
	  #endif
	  goto ret;
	}
#endif
    }
