switch (cmd) {
		case IIOCGETDVR:
			return (TTY_DV +
				(NET_DV << 8) +
				(INF_DV << 16));
		case IIOCGETCPS:
			if (arg) {
				ulong __user *p = argp;
				int i;
				if (!access_ok(VERIFY_WRITE, p,
					       sizeof(ulong) * ISDN_MAX_CHANNELS * 2))
					return -EFAULT;
				for (i = 0; i < ISDN_MAX_CHANNELS; i++) {
					put_user(dev->ibytes[i], p++);
					put_user(dev->obytes[i], p++);
				}
				return 0;
			} else
				return -EINVAL;
			break;
#ifdef CONFIG_NETDEVICES
		case IIOCNETGPN:
			/* Get peer phone number of a connected
			 * isdn network interface */
			if (arg) {
				if (copy_from_user(&phone, argp, sizeof(phone)))
					return -EFAULT;
				return isdn_net_getpeer(&phone, argp);
			} else
				return -EINVAL;
#endif
		default:
			return -EINVAL;
		}
