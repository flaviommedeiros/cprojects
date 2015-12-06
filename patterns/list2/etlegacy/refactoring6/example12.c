if (cent->processedFrame == cg.clientFrame
#ifdef FEATURE_MULTIVIEW
	    && cg.mvTotalClients < 2
#endif
	    )
	{
		return qtrue;
	}
