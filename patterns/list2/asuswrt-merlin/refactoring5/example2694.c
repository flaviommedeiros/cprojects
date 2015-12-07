#ifdef ENABLE_MANAGEMENT
if (ce_defined && management && management_query_remote_enabled(management))
	  {
	    /* allow management interface to override connection entry details */
	    ce_defined = ce_management_query_remote(c, remote_ip_hint);
	    if (IS_SIG (c))
	      break;
	  }
        else
#endif
	if (remote_ip_hint)
	  c->options.ce.remote = remote_ip_hint;
