if (daemon->dhcp || daemon->doing_dhcp6)
	  {
	    lease_prune(NULL, now);
	    lease_update_file(now);
	  }
#ifdef HAVE_DHCP6
	else if (daemon->doing_ra)
	  /* Not doing DHCP, so no lease system, manage alarms for ra only */
	    send_alarm(periodic_ra(now), now);
#endif
