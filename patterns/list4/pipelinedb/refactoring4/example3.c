#ifdef WIN32
if (WaitForSingleObject(termEvent, 0) == WAIT_OBJECT_0)
#else
	if (wantAbort)
#endif
		exit_horribly(modulename, "worker is terminating\n");
