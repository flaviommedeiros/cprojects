if ((request->listener->type != RAD_LISTEN_NONE) &&
#ifdef WITH_ACCOUNTING
	    (request->listener->type != RAD_LISTEN_ACCT) &&
#endif
#ifdef WITH_COA
	    (request->listener->type != RAD_LISTEN_COA) &&
#endif
	    (request->listener->type != RAD_LISTEN_AUTH)) return;
