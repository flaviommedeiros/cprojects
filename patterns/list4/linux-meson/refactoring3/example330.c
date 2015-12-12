switch (cmd) {
	case LPSETTIMEOUT:
		if (compat_get_timeval(&par_timeout, compat_ptr(arg))) {
			ret = -EFAULT;
			break;
		}
		ret = lp_set_timeout(minor, &par_timeout);
		break;
#ifdef LP_STATS
	case LPGETSTATS:
		/* FIXME: add an implementation if you set LP_STATS */
		ret = -EINVAL;
		break;
#endif
	default:
		ret = lp_do_ioctl(minor, cmd, arg, compat_ptr(arg));
		break;
	}
