switch (c)
	{

	case CT_CHAR:
	  /* scan arbitrary characters (sets NOSKIP) */
	  if (width == 0)
	    width = 1;
          if (flags & LONG) 
            {
              if ((flags & SUPPRESS) == 0)
                wcp = va_arg(ap, wchar_t *);
              else
                wcp = NULL;
              n = 0;
              while (width != 0) 
                {
                  
                  if (n == MB_CUR_MAX)
                    goto input_failure;
                  #ifndef SMALL_SCANF
                  buf[n++] = *fp->_p;
                  fp->_r -= 1;
                  fp->_p += 1;
                  memset((void *)&state, '\0', sizeof(mbstate_t));
                  if ((mbslen = _mbrtowc_r(rptr, wcp, buf, n, &state)) 
                                                         == (size_t)-1)
                    goto input_failure; /* Invalid sequence */
                  #else
                     buf[n++] = *fp->_p;
                  	*fp->_p = new_getchar();
							 						 
						#endif                 
                  
                  if (mbslen == 0 && !(flags & SUPPRESS))
                    *wcp = L'\0';
                  if (mbslen != (size_t)-2) /* Incomplete sequence */
                    {
                      nread += n;
                      width -= 1;
                      if (!(flags & SUPPRESS))
                        wcp += 1;
                      n = 0;
                    }
                  #ifndef SMALL_SCANF
                  if (BufferEmpty) 
	            {
                      if (n != 0) 
                        goto input_failure;
                      break;
                    }
                  #endif
                }
              if (!(flags & SUPPRESS))
                nassigned++;
            } 
          else if (flags & SUPPRESS) 
	    {
	      size_t sum = 0;
	      for (;;)
		{
		  if ((n = fp->_r) < (int)width)
		    {
		      sum += n;
		      width -= n;	
		      #ifndef SMALL_SCANF          
		      fp->_p += n;		      
		      if (__srefill (fp))
			{
			  if (sum == 0)
			    goto input_failure;
			  break;
			}
			  #else
			  *fp->_p = new_getchar();			  
			  #endif
			 
		    }
		  else
		    {
		      sum += width;
		      fp->_r -= width;
		      #ifndef SMALL_SCANF
		      fp->_p += width;
		      #else
		      *fp->_p = new_getchar();
		      #endif
		      
		      break;
		    }
		}
	      nread += sum;
	    }
	  else
	    {
		
			#ifndef SMALL_SCANF 
	      size_t r = fread ((_PTR) va_arg (ap, char *), 1, width, fp);
	      if (r == 0)
		   goto input_failure;
	      nread += r;
	      nassigned++;
	     	      
	      #else
	      bufread=(_PTR)va_arg(ap,char *);
	      int r;
	      for (r=0;r<width;r++){	      	
	      	*bufread++= *fp->_p;
	      	if ( r+1 < width){
	      	*fp->_p = new_getchar();
	      	}
	     	 }
	     	#endif          	  	  
	    }
	  break;

	case CT_CCL:
	  /* scan a (nonempty) character class (sets NOSKIP) */
	  if (width == 0)
	    width = ~0;		/* `infinity' */
	  /* take only those things in the class */
	  if (flags & SUPPRESS)
	    {
	      n = 0;
	      while (ccltab[*fp->_p])
		{
		  #ifndef SMALL_SCANF
		  n++, fp->_r--, fp->_p++;
		  if (--width == 0)
		    break;
		  if (BufferEmpty)
		    {
		      if (n == 0)
			goto input_failure;
		      break;
		    }
		   #else
		    n++;
		    fp->_r++;
		    *fp->_p = new_getchar();
		   #endif
		   
		}
	      if (n == 0)
		goto match_failure;
	    }
	  else
	    {
	      p0 = p = va_arg (ap, char *);
	      while (ccltab[*fp->_p])
		{
		  fp->_r--;
		  #ifndef SMALL_SCANF
		  *p++ = *fp->_p++;
		  if (--width == 0)
		    break;
		  if (BufferEmpty)
		    {
		      if (p == p0)
			goto input_failure;
		      break;
		    }
		  #else
		   *p++ = *fp->_p;
		  	*fp->_p= new_getchar();
		  	if (--width == 0)
		    break;
		  #endif
		  
		}
	      n = p - p0;
	      if (n == 0)
		goto match_failure;
	      *p = 0;
	      nassigned++;
	    }
	  nread += n;
	  break;

	case CT_STRING:
	  /* like CCL, but zero-length string OK, & no NOSKIP */
	  
	  if (width == 0)
            width = (size_t)~0;
          if (flags & LONG) 
            {
              /* Process %S and %ls placeholders */
              if ((flags & SUPPRESS) == 0)
                wcp = va_arg(ap, wchar_t *);
              else
                wcp = &wc;
              n = 0;
              while (!isspace(*fp->_p) && width != 0) 
                {
                  if (n == MB_CUR_MAX)
                    goto input_failure;
                  buf[n++] = *fp->_p;
                  fp->_r -= 1;
                  #ifndef SMALL_SCANF
                  fp->_p += 1;
                  memset((void *)&state, '\0', sizeof(mbstate_t));
                  if ((mbslen = _mbrtowc_r(rptr, wcp, buf, n, &state)) 
                                                        == (size_t)-1)
                    goto input_failure;
                  #else
                  *fp->_p = new_getchar();
                  #endif
                  
                  if (mbslen == 0)
                    *wcp = L'\0';
                  
                  if (mbslen != (size_t)-2) /* Incomplete sequence */
                    {
                      if (iswspace(*wcp)) 
                        {
                          
                          while (n != 0)
                            #ifndef SMALL_SCANF
                            ungetc(buf[--n], fp);
                            #else
                            __io_ungetc(buf[--n]);
                            #endif
                          break;
                         
                        }
                        
                      nread += n;
                      width -= 1;
                      if ((flags & SUPPRESS) == 0)
                        wcp += 1;
                      n = 0;
                    }
       				#ifndef SMALL_SCANF
                  if (BufferEmpty) 
                    {
                      if (n != 0)
                        goto input_failure;
                      break;
                    }
                 #endif
                
                }
              if (!(flags & SUPPRESS)) 
                {
                  *wcp = L'\0';
                  nassigned++;
                }
            }
          else if (flags & SUPPRESS) 
	    {
	      n = 0;
	      while (!isspace (*fp->_p))
		{
		  #ifndef SMALL_SCANF
		  n++, fp->_r--, fp->_p++;
		  if (--width == 0)
		    break;
		  if (BufferEmpty)
		    break;
		 #else
		    n++;
		    *fp->_p = new_getchar();		    
		    if (*fp->_p == '\0') break;
		  #endif
		  
		}
	      nread += n;
	    }
	  else
	    {
	      p0 = p = va_arg (ap, char *);
	      while (!isspace (*fp->_p))
		{
		  #ifndef SMALL_SCANF
		  fp->_r--;
		  *p++ = *fp->_p++;
		  if (--width == 0)
		    break;
		  if (BufferEmpty)
		    break;
		  #else
		    *p++=*fp->_p;
		    *fp->_p = new_getchar();		    
		    if (*fp->_p == '\0') break;
		  #endif
	 
		  
		}
	      *p = 0;
	      nread += p - p0;
	      nassigned++;
	    }
	  continue;

	case CT_INT:
	  /* scan an integer as if by strtol/strtoul */
#ifdef hardway
	  if (width == 0 || width > sizeof (buf) - 1)
	    width = sizeof (buf) - 1;
#else
	  /* size_t is unsigned, hence this optimisation */
	  if (--width > sizeof (buf) - 2)
	    width = sizeof (buf) - 2;
	  width++;
#endif
	  flags |= SIGNOK | NDIGITS | NZDIGITS;
	  for (p = buf; width; width--)
	    {     
	      c = *fp->_p;
	      /*
	       * Switch on the character; `goto ok' if we
	       * accept it as a part of number.
	       */
	      switch (c)
		{
		  /*
		   * The digit 0 is always legal, but is special.
		   * For %i conversions, if no digits (zero or nonzero)
		   * have been scanned (only signs), we will have base==0.
		   * In that case, we should set it to 8 and enable 0x
		   * prefixing. Also, if we have not scanned zero digits
		   * before this, do not turn off prefixing (someone else
		   * will turn it off if we have scanned any nonzero digits).
		   */
		case '0':
		  if (base == 0)
		    {
		      base = 8;
		      flags |= PFXOK;
		    }
		  if (flags & NZDIGITS)
		    flags &= ~(SIGNOK | NZDIGITS | NDIGITS);
		  else
		    flags &= ~(SIGNOK | PFXOK | NDIGITS);
		  goto ok;

		  /* 1 through 7 always legal */
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		  base = basefix[base];
		  flags &= ~(SIGNOK | PFXOK | NDIGITS);
		  goto ok;

		  /* digits 8 and 9 ok iff decimal or hex */
		case '8':
		case '9':
		  base = basefix[base];
		  if (base <= 8)
		    break;	/* not legal here */
		  flags &= ~(SIGNOK | PFXOK | NDIGITS);
		  goto ok;

		  /* letters ok iff hex */
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		  /* no need to fix base here */
		  if (base <= 10)
		    break;	/* not legal here */
		  flags &= ~(SIGNOK | PFXOK | NDIGITS);
		  goto ok;

		  /* sign ok only as first character */
		case '+':
		case '-':
		  if (flags & SIGNOK)
		    {
		      flags &= ~SIGNOK;
		      goto ok;
		    }
		  break;

		  /* x ok iff flag still set & 2nd char */
		case 'x':
		case 'X':
		  if (flags & PFXOK && p == buf + 1)
		    {
		      base = 16;/* if %i */
		      flags &= ~PFXOK;
		      goto ok;
		    }		  
		  break;
		}
	      /*
	       * If we got here, c is not a legal character
	       * for a number.  Stop accumulating digits.
	       */
		
	      break;
	    ok:
	      /*
	       * c is legal: store it and look at the next.
	       */
	      *p++ = c;
	      #ifndef SMALL_SCANF
       	 if (--fp->_r > 0)
				fp->_p++;
	       else	     
	     		if (__srefill (fp))
		     	break;		/* EOF */
		   #else
		   	   
		    *fp->_p = new_getchar();	
		         		   
		   #endif
		   	     
     	}
	  /*
	   * If we had only a sign, it is no good; push back the sign.
	   * If the number ends in `x', it was [sign] '0' 'x', so push back
	   * the x and treat it as [sign] '0'.
	   */
	  
	  if (flags & NDIGITS)
	    {
	   if (p > buf)
	       #ifndef SMALL_SCANF
				_CAST_VOID ungetc (*(u_char *)-- p, fp);
			 #else
				_CAST_VOID __io_ungetc (*(u_char *)-- p);
			 #endif
	      goto match_failure;

	    }
	 
	  c = ((u_char *) p)[-1];
	  if (c == 'x' || c == 'X')
	    {
	      --p;
	      #ifndef SMALL_SCANF
	      /*(void)*/ ungetc (c, fp);
	      #else 
	      	__io_ungetc (c);
	      #endif
	  
	    }
	  if ((flags & SUPPRESS) == 0)
	    {
	      u_long res;

	      *p = 0;
	      res = (*ccfn) (rptr, buf, (char **) NULL, base);
	      if (flags & POINTER)
		*(va_arg (ap, _PTR *)) = (_PTR) (unsigned _POINTER_INT) res;
	      else if (flags & CHAR)
		{
		  cp = va_arg (ap, char *);
		  *cp = res;
		}
	      else if (flags & SHORT)
		{
		  sp = va_arg (ap, short *);
		  *sp = res;
		}
	      else if (flags & LONG)
		{
		  lp = va_arg (ap, long *);
		  *lp = res;
		}
#ifndef _NO_LONGLONG
	      else if (flags & LONGDBL)
		{
		  u_long_long resll;
		  if (ccfn == _strtoul_r)
		    resll = _strtoull_r (rptr, buf, (char **) NULL, base);
		  else
		    resll = _strtoll_r (rptr, buf, (char **) NULL, base);
		  llp = va_arg (ap, long long*);
		  *llp = resll;
		}
#endif
	      else
		{
		  ip = va_arg (ap, int *);
		  *ip = res;
		}
	      nassigned++;
	    }
	  nread += p - buf;
	  break;

#ifdef FLOATING_POINT
	case CT_FLOAT:
	{
	  /* scan a floating point number as if by strtod */
	  /* This code used to assume that the number of digits is reasonable.
	     However, ANSI / ISO C makes no such stipulation; we have to get
	     exact results even when there is an unreasonable amount of
	     leading zeroes.  */
	  long leading_zeroes = 0;
	  long zeroes, exp_adjust;
	  char *exp_start = NULL;
#ifdef hardway
	  if (width == 0 || width > sizeof (buf) - 1)
	    width = sizeof (buf) - 1;
#else
	  /* size_t is unsigned, hence this optimisation */
	  if (--width > sizeof (buf) - 2)
	    width = sizeof (buf) - 2;
	  width++;
#endif
	  flags |= SIGNOK | NDIGITS | DPTOK | EXPOK;
	  zeroes = 0;
	  exp_adjust = 0;
	  for (p = buf; width; )
	    {
	      c = *fp->_p;
	      /*
	       * This code mimicks the integer conversion
	       * code, but is much simpler.
	       */
	      switch (c)
		{

		case '0':
		  if (flags & NDIGITS)
		    {
		      flags &= ~SIGNOK;
		      zeroes++;
		      goto fskip;
		    }
		  /* Fall through.  */
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		  flags &= ~(SIGNOK | NDIGITS);
		  goto fok;

		case '+':
		case '-':
		  if (flags & SIGNOK)
		    {
		      flags &= ~SIGNOK;
		      goto fok;
		    }
		  break;
		case '.':
		  if (flags & DPTOK)
		    {
		      flags &= ~(SIGNOK | DPTOK);
		      leading_zeroes = zeroes;
		      goto fok;
		    }
		  break;
		case 'e':
		case 'E':
		  /* no exponent without some digits */
		  if ((flags & (NDIGITS | EXPOK)) == EXPOK
		      || ((flags & EXPOK) && zeroes))
		    {
		      if (! (flags & DPTOK))
			{
			  exp_adjust = zeroes - leading_zeroes;
			  exp_start = p;
			}
		      flags =
			(flags & ~(EXPOK | DPTOK)) |
			SIGNOK | NDIGITS;
		      zeroes = 0;
		      goto fok;
		    }
		  break;
		}
	      break;
	    fok:
	      *p++ = c;
	    fskip:
	      width--;
              ++nread;
         #ifndef SMALL_SCANF
	      if (--fp->_r > 0)
		fp->_p++;
	      else
	      if (__srefill (fp))
		break;		/* EOF */
		  #else
		     *fp->_p = new_getchar();
		    if ( (47<*fp->_p<58) && (64<*fp->_p < 71) && (96<*fp->_p<103) ){
		       ;
		    }
		    else
		    {
		       break;
		    }
		  #endif 
	    }
	  if (zeroes)
	    flags &= ~NDIGITS;
	  /*
	   * If no digits, might be missing exponent digits
	   * (just give back the exponent) or might be missing
	   * regular digits, but had sign and/or decimal point.
	   */
	  if (flags & NDIGITS)
	    {
	      if (flags & EXPOK)
		{
		  /* no digits at all */
		
		  while (p > buf)
        {
            #ifndef SMALL_SCANF
		      ungetc (*(u_char *)-- p, fp);
		      #else
		      __io_ungetc(*(u_char *)-- p);
		      #endif
            --nread;
         }
                    
		  goto match_failure;

		}
		  
	      /* just a bad exponent (e and maybe sign) */
	      c = *(u_char *)-- p;
              --nread;
	      if (c != 'e' && c != 'E')
		{
		#ifndef SMALL_SCANF
		  _CAST_VOID ungetc (c, fp);	/* sign */
		#else
		  _CAST_VOID __io_ungetc (c);
		#endif
		  c = *(u_char *)-- p;
                  --nread;
		}
		#ifndef SMALL_SCANF
	      _CAST_VOID ungetc (c, fp);
	   #else
	      _CAST_VOID __io_ungetc (c);
	   #endif
	  
	    }
	  if ((flags & SUPPRESS) == 0)
	    {
	      double res = 0;
#ifdef _NO_LONGDBL
#define QUAD_RES res;
#else  /* !_NO_LONG_DBL */
	      long double qres = 0;
#define QUAD_RES qres;
#endif /* !_NO_LONG_DBL */
	      long new_exp = 0;

	      *p = 0;
	      if ((flags & (DPTOK | EXPOK)) == EXPOK)
		{
		  exp_adjust = zeroes - leading_zeroes;
		  new_exp = -exp_adjust;
		  exp_start = p;
		}
	      else if (exp_adjust)
                new_exp = _strtol_r (rptr, (exp_start + 1), NULL, 10) - exp_adjust;
	      if (exp_adjust)
		{

		  /* If there might not be enough space for the new exponent,
		     truncate some trailing digits to make room.  */
		  if (exp_start >= buf + sizeof (buf) - MAX_LONG_LEN)
		    exp_start = buf + sizeof (buf) - MAX_LONG_LEN - 1;
           sprintf (exp_start, "e%ld", new_exp);
		}

	      /* Current _strtold routine is markedly slower than 
	         _strtod_r.  Only use it if we have a long double
	         result.  */
#ifndef _NO_LONGDBL /* !_NO_LONGDBL */
	      if (flags & LONGDBL)
	      	qres = _strtold (buf, NULL);
	      else
#endif
	        res = _strtod_r (rptr, buf, NULL);
	      if (flags & LONG)
		{
		  dp = va_arg (ap, double *);
		  *dp = res;
		}
	      else if (flags & LONGDBL)
		{
		  ldp = va_arg (ap, _LONG_DOUBLE *);
		  *ldp = QUAD_RES;
		}
	      else
		{
		  flp = va_arg (ap, float *);
		  *flp = res;
		}
	      nassigned++;
	    }
	  break;
	}
#endif /* FLOATING_POINT */

	}
