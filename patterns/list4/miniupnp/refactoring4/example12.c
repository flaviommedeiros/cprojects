#ifndef ENABLE_IPV6
if(SendSSDPGoodbye(snotify, addr_count) < 0)
#else
		if(SendSSDPGoodbye(snotify, addr_count * 2) < 0)
#endif
		{
			syslog(LOG_ERR, "Failed to broadcast good-bye notifications");
		}
