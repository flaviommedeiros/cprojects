#ifdef HAVE_DNSSEC
if (option_bool(OPT_DNSSEC_VALID) && *sval == NAME_ESCAPE)
	    *p++ = (*(++sval))-1;
	  else
#endif		
	    *p++ = *sval;
