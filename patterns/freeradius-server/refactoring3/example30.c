switch (action) {
	case FR_ACTION_DUP:
		if (request->reply->code != 0) {
			request->listener->send(request->listener, request);
		} else {
			RDEBUG("No reply.  Ignoring retransmit");
		}

		/*
		 *	Double the cleanup_delay to catch retransmits.
		 */
		when = request->reply->timestamp;
		request->delay += request->delay;
		when.tv_sec += request->delay;

		STATE_MACHINE_TIMER(FR_ACTION_TIMER);
		break;

#ifdef WITH_PROXY
	case FR_ACTION_PROXY_REPLY:
		proxy_reply_too_late(request);
		break;
#endif

	case FR_ACTION_TIMER:
		fr_event_now(el, &now);

		rad_assert(request->root->cleanup_delay > 0);

		when = request->reply->timestamp;
		when.tv_sec += request->root->cleanup_delay;

		if (timercmp(&when, &now, >)) {
#ifdef DEBUG_STATE_MACHINE
			if (rad_debug_lvl) printf("(%u) ********\tNEXT-STATE %s -> %s\n", request->number, __FUNCTION__, "request_cleanup_delay");
#endif
			STATE_MACHINE_TIMER(FR_ACTION_TIMER);
			return;
		} /* else it's time to clean up */

		request_done(request, REQUEST_DONE);
		break;

	default:
		RDEBUG3("%s: Ignoring action %s", __FUNCTION__, action_codes[action]);
		break;
	}
