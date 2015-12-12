struct testcase_t bufferevent_testcases[] = {

	LEGACY(bufferevent, TT_ISOLATED),
	LEGACY(bufferevent_pair, TT_ISOLATED),
	LEGACY(bufferevent_watermarks, TT_ISOLATED),
	LEGACY(bufferevent_pair_watermarks, TT_ISOLATED),
	LEGACY(bufferevent_filters, TT_ISOLATED),
	LEGACY(bufferevent_pair_filters, TT_ISOLATED),
	{ "bufferevent_connect", test_bufferevent_connect, TT_FORK|TT_NEED_BASE,
	  &basic_setup, (void*)"" },
	{ "bufferevent_connect_defer", test_bufferevent_connect,
	  TT_FORK|TT_NEED_BASE, &basic_setup, (void*)"defer" },
	{ "bufferevent_connect_lock", test_bufferevent_connect,
	  TT_FORK|TT_NEED_BASE|TT_NEED_THREADS, &basic_setup, (void*)"lock" },
	{ "bufferevent_connect_lock_defer", test_bufferevent_connect,
	  TT_FORK|TT_NEED_BASE|TT_NEED_THREADS, &basic_setup,
	  (void*)"defer lock" },
	{ "bufferevent_connect_unlocked_cbs", test_bufferevent_connect,
	  TT_FORK|TT_NEED_BASE|TT_NEED_THREADS, &basic_setup,
	  (void*)"lock defer unlocked" },
	{ "bufferevent_connect_fail", test_bufferevent_connect_fail,
	  TT_FORK|TT_NEED_BASE, &basic_setup, NULL },
	{ "bufferevent_timeout", test_bufferevent_timeouts,
	  TT_FORK|TT_NEED_BASE|TT_NEED_SOCKETPAIR, &basic_setup, (void*)"" },
	{ "bufferevent_timeout_pair", test_bufferevent_timeouts,
	  TT_FORK|TT_NEED_BASE, &basic_setup, (void*)"pair" },
	{ "bufferevent_timeout_filter", test_bufferevent_timeouts,
	  TT_FORK|TT_NEED_BASE, &basic_setup, (void*)"filter" },
	{ "bufferevent_timeout_filter_pair", test_bufferevent_timeouts,
	  TT_FORK|TT_NEED_BASE, &basic_setup, (void*)"filter pair" },
#ifdef _EVENT_HAVE_LIBZ
	LEGACY(bufferevent_zlib, TT_ISOLATED),
#else
	{ "bufferevent_zlib", NULL, TT_SKIP, NULL, NULL },
#endif

	END_OF_TESTCASES,
};
