#ifdef ENABLE_FEATURE_SHAPER
if (c->options.shaper)
	    msg (M_INFO, "NOTE: --fast-io is disabled since we are using --shaper");
	  else
#endif
	    {
	      c->c2.fast_io = true;
	    }
