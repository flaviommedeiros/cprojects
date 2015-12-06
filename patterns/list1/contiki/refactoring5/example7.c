#ifndef _DOUBLE_IS_32BITS
if (d1)
    {
      y = d1;
      k = small_lo0bits (&y);
      if (k)
	{
         x[0] = y | z << (32 - k);
	  z >>= k;
	}
      else
	x[0] = y;
      i = b->_wds = (x[1] = z) ? 2 : 1;
    }
  else
#endif
    {
#ifdef DEBUG
      if (!z)
	Bug ("Zero passed to d2b");
#endif
      k = small_lo0bits (&z);
      x[0] = z;
      i = b->_wds = 1;
#ifndef _DOUBLE_IS_32BITS
      k += 32;
#endif
    }
