#ifdef USE_RTS
if( lp->useRTS == 1 ) {
		DBG_TRACE( DbgInfo, "Skipping wireless stats, in RTS mode\n" );
	} else
#endif
	{
		pStats = wl_wireless_stats( dev );
	}
