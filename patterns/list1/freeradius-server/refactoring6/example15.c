if ((!request->username)
#ifdef WITH_PROXY
	    || (request->proxy != NULL)
#endif
	    ) {

		RDEBUG2("Proxy reply, or no User-Name.  Ignoring");
		return RLM_MODULE_NOOP;
	}
