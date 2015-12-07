#ifdef SIOCBRDELIF
if (err < 0)
#endif		
	{
		unsigned long args[4] = { BRCTL_DEL_IF, ifindex, 0, 0 };
					  
		ifr.ifr_data = (char *) args;
		err = ioctl(br_socket_fd, SIOCDEVPRIVATE, &ifr);
	}
