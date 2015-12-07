#ifdef SIOCBRDELBR
if (ret < 0)
#endif
	{
		char _br[IFNAMSIZ];
		unsigned long arg[3] 
			= { BRCTL_DEL_BRIDGE, (unsigned long) _br };

		strncpy(_br, brname, IFNAMSIZ);
		ret = ioctl(br_socket_fd, SIOCSIFBR, arg);
	}
