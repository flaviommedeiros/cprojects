if(current_wrd_mode == WRD_TRACE_MIMPI)
	WinEvent();
#ifdef ENABLE_SHERRY
    else if(current_wrd_mode == WRD_TRACE_SHERRY)
	x_sry_event();
#endif
