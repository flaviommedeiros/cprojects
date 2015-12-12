#ifdef CONFIG_COMPAT
if (count == sizeof(struct compat_raw1394_req) &&
   	    sizeof(struct compat_raw1394_req) !=
			sizeof(struct raw1394_request)) {
		buffer = raw1394_compat_write(buffer);
		if (IS_ERR((__force void *)buffer))
			return PTR_ERR((__force void *)buffer);
	} else
#endif
	if (count != sizeof(struct raw1394_request)) {
		return -EINVAL;
	}
