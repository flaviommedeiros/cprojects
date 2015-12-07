#ifdef WITH_SYSLOG
if( !lp_syslog_only() )
#endif
	{
		if( !dbf ) {
			mode_t oldumask = umask( 022 );

			dbf = x_fopen( debugf, O_WRONLY|O_APPEND|O_CREAT, 0644 );
			(void)umask( oldumask );
			if( dbf ) {
				x_setbuf( dbf, NULL );
			} else {
				errno = old_errno;
				return(0);
			}
		}
	}
