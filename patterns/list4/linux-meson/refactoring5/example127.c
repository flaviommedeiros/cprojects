#ifdef CONFIG_COMPAT
if(is_compat_task())
		return rtw_ioctl_compat_wext_private( dev, rq );
	else
#endif // CONFIG_COMPAT
		return rtw_ioctl_standard_wext_private( dev, rq );
