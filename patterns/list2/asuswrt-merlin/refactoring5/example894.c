#ifdef CONFIG_COMPAT
if (count == sizeof(struct compat_raw1394_req)) {
		/* ok */
	} else
#endif
	if (count != sizeof(struct raw1394_request)) {
		return -EINVAL;
	}
