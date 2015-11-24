if (((home->state == HOME_STATE_ALIVE) ||
		     (home->state == HOME_STATE_UNKNOWN))
#ifdef WITH_TCP
		    && (home->proto != IPPROTO_TCP)
#endif
			) {
			home->response_timeouts++;
			if (home->response_timeouts >= home->max_response_timeouts)
				mark_home_server_zombie(home, &now, response_window);
		}
