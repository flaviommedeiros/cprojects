switch(device_type) {
		default:
			device_type = DEVICE_TYPE_TUN;
		case DEVICE_TYPE_TUN:
#ifdef TUNSIFHEAD
		{	
			const int zero = 0;
			if(ioctl(device_fd, TUNSIFHEAD, &zero, sizeof zero) == -1) {
				logger(LOG_ERR, "System call `%s' failed: %s", "ioctl", strerror(errno));
				return false;
			}
		}
#endif
#if defined(TUNSIFMODE) && defined(IFF_BROADCAST) && defined(IFF_MULTICAST)
		{
			const int mode = IFF_BROADCAST | IFF_MULTICAST;
			ioctl(device_fd, TUNSIFMODE, &mode, sizeof mode);
		}
#endif

			device_info = "Generic BSD tun device";
			break;
		case DEVICE_TYPE_TUNIFHEAD:
#ifdef TUNSIFHEAD
		{
			const int one = 1;
			if(ioctl(device_fd, TUNSIFHEAD, &one, sizeof one) == -1) {
				logger(LOG_ERR, "System call `%s' failed: %s", "ioctl", strerror(errno));
				return false;
			}
		}
#endif
#if defined(TUNSIFMODE) && defined(IFF_BROADCAST) && defined(IFF_MULTICAST)
		{
				const int mode = IFF_BROADCAST | IFF_MULTICAST;
				ioctl(device_fd, TUNSIFMODE, &mode, sizeof mode);
		}
#endif

			device_info = "Generic BSD tun device";
			break;
		case DEVICE_TYPE_TAP:
			if(routing_mode == RMODE_ROUTER)
				overwrite_mac = true;
			device_info = "Generic BSD tap device";
#ifdef TAPGIFNAME
			{
				struct ifreq ifr;
				if(ioctl(device_fd, TAPGIFNAME, (void*)&ifr) == 0) {
					if(iface)
						free(iface);
					iface = xstrdup(ifr.ifr_name);
				}
			}
			
#endif
			break;
#ifdef ENABLE_TUNEMU
		case DEVICE_TYPE_TUNEMU:
        		device_info = "BSD tunemu device";
			break;
#endif
	}
