struct testcase_t thread_testcases[] = {
	{ "basic", thread_basic, TT_FORK|TT_NEED_THREADS|TT_NEED_BASE,
	  &basic_setup, NULL },
#ifndef _WIN32
	{ "forking", thread_basic, TT_FORK|TT_NEED_THREADS|TT_NEED_BASE,
	  &basic_setup, (char*)"forking" },
#endif
	TEST(conditions_simple),
	{ "deferred_cb_skew", thread_deferred_cb_skew,
	  TT_FORK|TT_NEED_THREADS|TT_OFF_BY_DEFAULT,
	  &basic_setup, NULL },
	TEST(no_events),
	END_OF_TESTCASES
};
