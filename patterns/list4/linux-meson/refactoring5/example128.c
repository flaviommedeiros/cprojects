#ifdef CONFIG_COMPAT
if (is_compat_task()) {
		/* User space is 32-bit, use compat ioctl */
		compat_android_wifi_priv_cmd compat_priv_cmd;

		if (copy_from_user(&compat_priv_cmd, ifr->ifr_data, sizeof(compat_android_wifi_priv_cmd))) {
			ret = -EFAULT;
			goto exit;
		}
		priv_cmd.buf = compat_ptr(compat_priv_cmd.buf);
		priv_cmd.used_len = compat_priv_cmd.used_len;
		priv_cmd.total_len = compat_priv_cmd.total_len;
	} else
#endif /* CONFIG_COMPAT */
	if (copy_from_user(&priv_cmd, ifr->ifr_data, sizeof(android_wifi_priv_cmd))) {
		ret = -EFAULT;
		goto exit;
	}
