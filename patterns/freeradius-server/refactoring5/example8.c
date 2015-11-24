#ifdef WITH_TCP
if (!request->proxy_listener ||
		    (request->proxy_listener->status >= RAD_LISTEN_STATUS_EOL)) {
			remove_from_proxy_hash(request);

			when = request->packet->timestamp;
			when.tv_sec += request->root->max_request_time;

			if (timercmp(&when, &now, >)) {
				RDEBUG("Waiting for client retransmission in order to do a proxy retransmit");
				STATE_MACHINE_TIMER(FR_ACTION_TIMER);
				return;
			}
		} else
#endif
		{
			/*
			 *	Wake up "response_window" time in the future.
			 *	i.e. when MY packet hasn't received a response.
			 *
			 *	Note that we DO NOT mark the home server as
			 *	zombie if it doesn't respond to us.  It may be
			 *	responding to other (better looking) packets.
			 */
			when = request->proxy->timestamp;
			timeradd(&when, response_window, &when);

			/*
			 *	Not at the response window.  Set the timer for
			 *	that.
			 */
			if (timercmp(&when, &now, >)) {
				struct timeval diff;
				timersub(&when, &now, &diff);

				RDEBUG("Expecting proxy response no later than %d.%06d seconds from now",
				       (int) diff.tv_sec, (int) diff.tv_usec);
				STATE_MACHINE_TIMER(FR_ACTION_TIMER);
				return;
			}
		}
