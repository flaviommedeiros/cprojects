#ifdef WITH_SYSLOG
if( !lp_syslog_only() )
#endif
	{
		va_start( ap, format_str );
		if(dbf)
			(void)x_vfprintf( dbf, format_str, ap );
		va_end( ap );
		if(dbf)
			(void)x_fflush( dbf );
	}
