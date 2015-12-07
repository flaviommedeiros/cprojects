#ifdef WITH_SYSLOG
if( !state.settings.syslog_only)
#endif
	{
		if( state.fd <= 0 ) {
			mode_t oldumask = umask( 022 );
			int fd = open( state.debugf, O_WRONLY|O_APPEND|O_CREAT, 0644 );
			(void)umask( oldumask );
			if(fd == -1) {
				errno = old_errno;
				goto done;
			}
			state.fd = fd;
		}
	}
