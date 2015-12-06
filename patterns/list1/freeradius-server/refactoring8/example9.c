void revive_home_server(void *ctx, UNUSED struct timeval *now)
{
	home_server_t *home = talloc_get_type_abort(ctx, home_server_t);
	char buffer[INET6_ADDRSTRLEN];

#ifdef WITH_TCP
	rad_assert(home->proto != IPPROTO_TCP);
#endif

	home->state = HOME_STATE_ALIVE;
	home->response_timeouts = 0;
	home_trigger(home, "home_server.alive");
	home->currently_outstanding = 0;
	gettimeofday(&home->revive_time, NULL);

	/*
	 *	Delete any outstanding events.
	 */
	ASSERT_MASTER;
	if (home->ev) fr_event_delete(el, &home->ev);

	PROXY("Marking home server %s port %d alive again... we have no idea if it really is alive or not.",
	      inet_ntop(home->ipaddr.af, &home->ipaddr.ipaddr, buffer, sizeof(buffer)),
	      home->port);
}
