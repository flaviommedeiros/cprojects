if (a.type == NA_IP
#ifdef FEATURE_IPV6
	    || a.type == NA_IP6
#endif
	    )
	{
		if (a.port == b.port)
		{
			return qtrue;
		}
	}
	else
	{
		return qtrue;
	}
