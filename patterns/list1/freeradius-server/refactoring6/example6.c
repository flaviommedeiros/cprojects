if ((request->num_proxied_requests > request->num_proxied_responses) &&
#ifdef WITH_TCP
		    (request->home_server->proto != IPPROTO_TCP) &&
#endif
		    timercmp(&now, &when, <)) {
			RDEBUG("Waiting for more responses from the home server");
			goto wait_some_more;
		}
