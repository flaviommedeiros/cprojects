#ifdef ENABLE_OCC
if (event_timeout_defined(&c->c2.explicit_exit_notification_interval))
	      {
		msg (D_STREAM_ERRORS, "Connection reset during exit notification period, ignoring [%d]", status);
		openvpn_sleep(1);
	      }
	    else
#endif
	      {
		register_signal (c, SIGUSR1, "connection-reset"); /* SOFT-SIGUSR1 -- TCP connection reset */
		msg (D_STREAM_ERRORS, "Connection reset, restarting [%d]", status);
	      }
