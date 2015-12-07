#ifdef WITH_SYSLOG
if( !state.settings.syslog_only)
#endif
	{
		va_start( ap, format_str );
		if (state.fd > 0)
			(void)vdprintf( state.fd, format_str, ap );
		va_end( ap );
	}
