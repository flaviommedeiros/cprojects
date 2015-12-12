switch (cmd) {
	case TUNSETNOCSUM:
		/* Disable/Enable checksum */
		if (arg) tun->flags |= TUN_NOCHECKSUM;
		else     tun->flags &= ~TUN_NOCHECKSUM;

		DBG(KERN_INFO "%s: checksum %s\n",
		    tun->dev->name, arg ? "disabled" : "enabled");
		break;

	case TUNSETPERSIST:
		/* Disable/Enable persist mode */
		if (arg) tun->flags |= TUN_PERSIST;
		else     tun->flags &= ~TUN_PERSIST;

		DBG(KERN_INFO "%s: persist %s\n",
		    tun->dev->name, arg ? "disabled" : "enabled");
		break;

	case TUNSETOWNER:
		/* Set owner of the device */
		tun->owner = (uid_t) arg;

		DBG(KERN_INFO "%s: owner set to %d\n", tun->dev->name, tun->owner);
		break;

	case TUNSETLINK:
		/* Only allow setting the type when the interface is down */
		if (tun->dev->flags & IFF_UP) {
			DBG(KERN_INFO "%s: Linktype set failed because interface is up\n",
				tun->dev->name);
			ret = -EBUSY;
			goto unlock;
		} else {
			tun->dev->type = (int) arg;
			DBG(KERN_INFO "%s: linktype set to %d\n", tun->dev->name, tun->dev->type);
		}
		break;
#ifdef TUN_DEBUG
	case TUNSETDEBUG:
		tun->debug = arg;
		break;
#endif
	case SIOCGIFFLAGS:
		ifr.ifr_flags = tun->if_flags;
		if (copy_to_user( argp, &ifr, sizeof ifr)) {
			ret = -EFAULT;
			goto unlock;
		}
		break;

	case SIOCSIFFLAGS:
		/** Set the character device's interface flags. Currently only
		 * IFF_PROMISC and IFF_ALLMULTI are used. */
		tun->if_flags = ifr.ifr_flags;
		DBG(KERN_INFO "%s: interface flags 0x%lx\n",
				tun->dev->name, tun->if_flags);
		break;
	case SIOCGIFHWADDR:
		/* Note: the actual net device's address may be different */
		memcpy(ifr.ifr_hwaddr.sa_data, tun->dev_addr,
				min(sizeof ifr.ifr_hwaddr.sa_data, sizeof tun->dev_addr));
		if (copy_to_user( argp, &ifr, sizeof ifr)) {
			ret = -EFAULT;
			goto unlock;
		}
		break;
	case SIOCSIFHWADDR:
	{
		/* try to set the actual net device's hw address */
		ret = dev_set_mac_address(tun->dev, &ifr.ifr_hwaddr);

		if (ret == 0) {
			/** Set the character device's hardware address. This is used when
			 * filtering packets being sent from the network device to the character
			 * device. */
			memcpy(tun->dev_addr, ifr.ifr_hwaddr.sa_data,
					min(sizeof ifr.ifr_hwaddr.sa_data, sizeof tun->dev_addr));
			DBG(KERN_DEBUG "%s: set hardware address: %x:%x:%x:%x:%x:%x\n",
					tun->dev->name,
					tun->dev_addr[0], tun->dev_addr[1], tun->dev_addr[2],
					tun->dev_addr[3], tun->dev_addr[4], tun->dev_addr[5]);
		}
		break;
	}
	default:
		ret = -EINVAL;
	}
