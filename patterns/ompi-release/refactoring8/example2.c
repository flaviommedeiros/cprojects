struct testcase_t signal_testcases[] = {
#ifndef WIN32
	LEGACY(simplesignal, TT_ISOLATED),
	LEGACY(multiplesignal, TT_ISOLATED),
	LEGACY(immediatesignal, TT_ISOLATED),
	LEGACY(signal_dealloc, TT_ISOLATED),
	LEGACY(signal_pipeloss, TT_ISOLATED),
	LEGACY(signal_switchbase, TT_ISOLATED|TT_NO_LOGS),
	LEGACY(signal_restore, TT_ISOLATED),
	LEGACY(signal_assert, TT_ISOLATED),
	LEGACY(signal_while_processing, TT_ISOLATED),
#endif
	END_OF_TESTCASES
};
