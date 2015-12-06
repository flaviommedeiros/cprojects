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
