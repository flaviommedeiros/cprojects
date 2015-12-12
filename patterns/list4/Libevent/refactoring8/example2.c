struct testcase_t dns_testcases[] = {
	DNS_LEGACY(server, TT_FORK|TT_NEED_BASE),
	DNS_LEGACY(gethostbyname, TT_FORK|TT_NEED_BASE|TT_NEED_DNS|TT_OFF_BY_DEFAULT),
	DNS_LEGACY(gethostbyname6, TT_FORK|TT_NEED_BASE|TT_NEED_DNS|TT_OFF_BY_DEFAULT),
	DNS_LEGACY(gethostbyaddr, TT_FORK|TT_NEED_BASE|TT_NEED_DNS|TT_OFF_BY_DEFAULT),
	{ "resolve_reverse", dns_resolve_reverse, TT_FORK|TT_OFF_BY_DEFAULT, NULL, NULL },
	{ "search", dns_search_test, TT_FORK|TT_NEED_BASE, &basic_setup, NULL },
	{ "search_cancel", dns_search_cancel_test,
	  TT_FORK|TT_NEED_BASE, &basic_setup, NULL },
	{ "retry", dns_retry_test, TT_FORK|TT_NEED_BASE|TT_NO_LOGS, &basic_setup, NULL },
	{ "retry_disable_when_inactive", dns_retry_disable_when_inactive_test,
	  TT_FORK|TT_NEED_BASE|TT_NO_LOGS, &basic_setup, NULL },
	{ "reissue", dns_reissue_test, TT_FORK|TT_NEED_BASE|TT_NO_LOGS, &basic_setup, NULL },
	{ "reissue_disable_when_inactive", dns_reissue_disable_when_inactive_test,
	  TT_FORK|TT_NEED_BASE|TT_NO_LOGS, &basic_setup, NULL },
	{ "inflight", dns_inflight_test, TT_FORK|TT_NEED_BASE, &basic_setup, NULL },
	{ "bufferevent_connect_hostname", test_bufferevent_connect_hostname,
	  TT_FORK|TT_NEED_BASE, &basic_setup, NULL },
	{ "disable_when_inactive", dns_disable_when_inactive_test,
	  TT_FORK|TT_NEED_BASE, &basic_setup, NULL },
	{ "disable_when_inactive_no_ns", dns_disable_when_inactive_no_ns_test,
	  TT_FORK|TT_NEED_BASE, &basic_setup, NULL },

	{ "getaddrinfo_async", test_getaddrinfo_async,
	  TT_FORK|TT_NEED_BASE, &basic_setup, (char*)"" },
	{ "getaddrinfo_cancel_stress", test_getaddrinfo_async_cancel_stress,
	  TT_FORK, NULL, NULL },

#ifdef EVENT_SET_MEM_FUNCTIONS_IMPLEMENTED
	{ "leak_shutdown", test_dbg_leak_shutdown, TT_FORK, &testleak_funcs, NULL },
	{ "leak_cancel", test_dbg_leak_cancel, TT_FORK, &testleak_funcs, NULL },

	{ "leak_resume", test_dbg_leak_resume_, TT_FORK, &testleak_funcs, NULL },
	{ "leak_cancel_and_resume", test_dbg_leak_cancel_and_resume_,
	  TT_FORK, &testleak_funcs, NULL },
	{ "leak_resume_send_err", test_dbg_leak_resume_send_err_,
	  TT_FORK, &testleak_funcs, NULL },
	{ "leak_cancel_and_resume_send_err", test_dbg_leak_cancel_and_resume_send_err_,
	  TT_FORK, &testleak_funcs, NULL },
#endif

	END_OF_TESTCASES
};
