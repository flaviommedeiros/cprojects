switch (action) {
	case FR_ACTION_DUP:
		ERROR("(%u) Discarding duplicate request from "
		      "client %s port %d - ID: %u due to delayed response",
		      request->number, request->client->shortname,
		      request->packet->src_port,request->packet->id);
		break;

#ifdef WITH_PROXY
	case FR_ACTION_PROXY_REPLY:
		proxy_reply_too_late(request);
		break;
#endif

	case FR_ACTION_TIMER:
		fr_event_now(el, &now);

		/*
		 *	See if it's time to send the reply.  If not,
		 *	we wait some more.
		 */
		when = request->reply->timestamp;

		tv_add(&when, request->response_delay.tv_sec * USEC);
		tv_add(&when, request->response_delay.tv_usec);

		if (timercmp(&when, &now, >)) {
#ifdef DEBUG_STATE_MACHINE
			if (rad_debug_lvl) printf("(%u) ********\tNEXT-STATE %s -> %s\n", request->number, __FUNCTION__, "request_response_delay");
#endif
			STATE_MACHINE_TIMER(FR_ACTION_TIMER);
			return;
		} /* else it's time to send the reject */

		RDEBUG2("Sending delayed response");
		request->listener->debug(request, request->reply, false);
		request->listener->send(request->listener, request);

		/*
		 *	Clean up the request.
		 */
		request_cleanup_delay_init(request);
		break;

	default:
		RDEBUG3("%s: Ignoring action %s", __FUNCTION__, action_codes[action]);
		break;
	}
