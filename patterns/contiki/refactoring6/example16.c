if ((j < 0) || ((j == 0) && !mode
#ifndef ROUND_BIASED
	      && !(word1 (d) & 1)
#endif
           ))
	    {
	      if (j1 > 0)
		{
		  
		  #ifdef _SMALL_PRINTF
		  if (b == &tab_b[0]){
		  		b = small_lshift (ptr, b, 1,&tab_blshift[0]);		
		  }
		  else {
		   	b = small_lshift (ptr, b, 1,&tab_b[0]);		
		  }
		  #else
		  b = lshift (ptr, b, 1);
		  #endif

		  j1 = small_cmp (b, S);
                 if (((j1 > 0) || ((j1 == 0) && (dig & 1)))
		      && dig++ == '9')
		    goto round_9_up;
		}
	      
	      *s++ = dig;
	      
	      goto ret;
	    }
