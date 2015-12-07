#ifdef HAVE_SCRIPT
if (daemon->lease_change_command)
	{
	  strcpy(daemon->dhcp_buff, daemon->lease_change_command);
	  strcat(daemon->dhcp_buff, " init");
	  leasestream = popen(daemon->dhcp_buff, "r");
	}
      else
#endif
	{
          file_dirty = dns_dirty = 0;
          return;
        }
