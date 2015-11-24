#ifndef No_leftright
if (leftright)
	{
	  /* Use Steele & White method of only
	   * generating digits needed.
	   */
	  eps.d = 0.5 / small_tens[ilim - 1] - eps.d;
	  for (i = 0;;)
	    {
	      L = d.d;
	      d.d -= L;
	      
	      *s++ = '0' + (int) L;
	      
	      if (d.d < eps.d)
		goto ret1;
	      if (1. - d.d < eps.d)
		goto bump_up;
	      if (++i >= ilim)
		break;
	      eps.d *= 10.;
	      d.d *= 10.;
	    }
	}
      else
	{
#endif
	  /* Generate ilim digits, then fix them up. */
	  eps.d *= small_tens[ilim - 1];
	  for (i = 1;; i++, d.d *= 10.)
	    {
	      L = d.d;
	      d.d -= L;	      
	      *s++ = '0' + (int) L;	      
	      if (i == ilim)
		{
		  if (d.d > 0.5 + eps.d)
		    goto bump_up;
		  else if (d.d < 0.5 - eps.d)
		    {		      
		      while (*--s == '0');
		      s++;		    
		      goto ret1;
		    }
		  break;
		}
	    }
#ifndef No_leftright
	}
