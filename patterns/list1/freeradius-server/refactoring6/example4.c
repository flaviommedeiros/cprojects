if (
#ifdef WITH_PROXY
		    !main_config.proxy_requests &&
#endif
		    ((comp == MOD_PRE_PROXY) ||
		     (comp == MOD_POST_PROXY))) {
			continue;
		}
