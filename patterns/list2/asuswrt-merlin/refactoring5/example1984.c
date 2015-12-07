#ifdef CONFIG_COMPAT
if (count == sizeof(struct compat_raw1394_req) &&
   	    sizeof(struct compat_raw1394_req) !=
			sizeof(struct raw1394_request)) {
		ret = raw1394_compat_read(buffer, &req->req);
	} else
#endif
	{
		if (copy_to_user(buffer, &req->req, sizeof(req->req))) {
			ret = -EFAULT;
			goto out;
		}
		ret = (ssize_t) sizeof(struct raw1394_request);
	}
