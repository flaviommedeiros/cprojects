switch (action) {
	case FR_ACTION_DUP:
#ifdef WITH_DETAIL
		rad_assert(request->listener != NULL);
#endif
		if (request->reply->code != 0) {
			request->listener->send(request->listener, request);
			return;
		} else {
			RDEBUG("No reply.  Ignoring retransmit");
		}
		break;

		/*
		 *	Mark the request as done.
		 */
	case FR_ACTION_DONE:
#ifdef HAVE_PTHREAD_H
		/*
		 *	If the child is still running, leave it alone.
		 */
		if (spawn_workers && (request->child_state <= REQUEST_RUNNING)) {
			break;
		}
#endif

#ifdef DEBUG_STATE_MACHINE
		if (rad_debug_lvl) printf("(%u) ********\tSTATE %s C-%s -> C-%s\t********\n",
				       request->number, __FUNCTION__,
				       child_state_names[request->child_state],
				       child_state_names[REQUEST_DONE]);
#endif
		request->child_state = REQUEST_DONE;
		break;

		/*
		 *	Called when the child is taking too long to
		 *	finish.  We've already marked it "please
		 *	stop", so we don't complain any more.
		 */
	case FR_ACTION_TIMER:
		break;

#ifdef WITH_PROXY
	case FR_ACTION_PROXY_REPLY:
		proxy_reply_too_late(request);
		break;
#endif

	default:
		break;
	}
