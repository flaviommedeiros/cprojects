if ((home->state == HOME_STATE_ALIVE) ||
#ifdef WITH_TCP
	    (home->proto == IPPROTO_TCP) ||
#endif
	    (home->ev != NULL)) {
		return;
	}
