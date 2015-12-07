#ifdef HAVE_DNSSEC
if (option_bool(OPT_DNSSEC_VALID))
		  {
		    if (c == 0 || c == '.' || c == NAME_ESCAPE)
		      {
			*cp++ = NAME_ESCAPE;
			*cp++ = c+1;
		      }
		    else
		      *cp++ = c; 
		  }
		else
#endif
		if (c != 0 && c != '.')
		  *cp++ = c;
		else
		  return 0;
