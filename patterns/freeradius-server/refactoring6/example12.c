if (
#ifdef WITH_PROXY
	    (request->proxy == NULL) &&
#endif
	    ((tmp = fr_pair_find_by_num(request->config, 0, PW_PROXY_TO_REALM, TAG_ANY)) != NULL)) {
		REALM *realm;

		realm = realm_find2(tmp->vp_strvalue);

		/*
		 *	Don't authenticate, as the request is going to
		 *	be proxied.
		 */
		if (realm && realm->auth_pool) {
			return RLM_MODULE_OK;
		}

		/*
		 *	Catch users who set Proxy-To-Realm to a LOCAL
		 *	realm (sigh).  But don't complain if it is
		 *	*the* LOCAL realm.
		 */
		if (realm &&(strcmp(realm->name, "LOCAL") != 0)) {
			RWDEBUG2("You set Proxy-To-Realm = %s, but it is a LOCAL realm!  Cancelling proxy request.", realm->name);
		}

		if (!realm) {
			RWDEBUG2("You set Proxy-To-Realm = %s, but the realm does not exist!  Cancelling invalid proxy request.", tmp->vp_strvalue);
		}
	}
