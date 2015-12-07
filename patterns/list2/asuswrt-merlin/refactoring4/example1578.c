#ifdef DNS_USE_CPU_CLOCK_FOR_ID
if (clock_gettime(CLOCK_MONOTONIC, &ts) == -1)
#else
	if (clock_gettime(CLOCK_REALTIME, &ts) == -1)
#endif
	event_err(1, "clock_gettime");
