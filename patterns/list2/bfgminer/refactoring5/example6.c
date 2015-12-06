#ifdef HAVE_CLOCK_GETTIME_MONOTONIC_RAW
if (_bfg_try_clock_gettime(CLOCK_MONOTONIC_RAW))
		applog(LOG_DEBUG, "Timers: Using clock_gettime(CLOCK_MONOTONIC_RAW)");
	else
#endif
	if (_bfg_try_clock_gettime(CLOCK_MONOTONIC))
	{
		applog(LOG_DEBUG, "Timers: Using clock_gettime(CLOCK_MONOTONIC)");
#ifdef HAVE_CLOCK_NANOSLEEP
		cgsleep_us_r = _cgsleep_us_r_monotonic;
#endif
	}
	else
#endif
#ifdef WIN32
	if (QueryPerformanceFrequency(&_perffreq) && _perffreq.QuadPart)
	{
		timer_set_now = _now_queryperformancecounter;
		applog(LOG_DEBUG, "Timers: Using QueryPerformanceCounter");
	}
	else
#endif
	{
		timer_set_now = _now_gettimeofday;
		applog(LOG_DEBUG, "Timers: Using gettimeofday");
	}
