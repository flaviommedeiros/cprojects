switch (seccomp_mode) {
	case SECCOMP_MODE_STRICT:
		ret = 0;
#ifdef TIF_NOTSC
		disable_TSC();
#endif
		break;
#ifdef CONFIG_SECCOMP_FILTER
	case SECCOMP_MODE_FILTER:
		ret = seccomp_attach_user_filter(filter);
		if (ret)
			goto out;
		break;
#endif
	default:
		goto out;
	}
