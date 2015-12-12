if (nd <= DBL_DIG
#ifndef Honor_FLT_ROUNDS
    && Flt_Rounds == 1
#endif
      )
  {
    if (!e)
      goto ret;
    if (e > 0)
    {
      if (e <= Ten_pmax)
      {
#ifdef Honor_FLT_ROUNDS
        /* round correctly FLT_ROUNDS = 2 or 3 */
        if (sign)
        {
          rv.d= -rv.d;
          sign= 0;
        }
#endif
        /* rv = */ rounded_product(dval(&rv), tens[e]);
        goto ret;
      }
      i= DBL_DIG - nd;
      if (e <= Ten_pmax + i)
      {
        /*
          A fancier test would sometimes let us do
          this for larger i values.
        */
#ifdef Honor_FLT_ROUNDS
        /* round correctly FLT_ROUNDS = 2 or 3 */
        if (sign)
        {
          rv.d= -rv.d;
          sign= 0;
        }
#endif
        e-= i;
        dval(&rv)*= tens[i];
        /* rv = */ rounded_product(dval(&rv), tens[e]);
        goto ret;
      }
    }
#ifndef Inaccurate_Divide
    else if (e >= -Ten_pmax)
    {
#ifdef Honor_FLT_ROUNDS
      /* round correctly FLT_ROUNDS = 2 or 3 */
      if (sign)
      {
        rv.d= -rv.d;
        sign= 0;
      }
#endif
      /* rv = */ rounded_quotient(dval(&rv), tens[-e]);
      goto ret;
    }
#endif
  }
