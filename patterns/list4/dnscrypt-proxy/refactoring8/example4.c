struct testcase_t thread_testcases[] = {
	{ "basic", thread_basic, TT_FORK|TT_NEED_THREADS|TT_NEED_BASE,
	  &basic_setup, NULL },
#ifndef WIN32
	{ "forking", thread_basic, TT_FORK|TT_NEED_THREADS|TT_NEED_BASE,
	  &basic_setup, (char*)"forking" },
#endif
	TEST(conditions_simple),
	TEST(deferred_cb_skew),
	END_OF_TESTCASES
};
