switch (cmd) {
	case CAPI_REGISTER:
		mutex_lock(&cdev->lock);

		if (cdev->ap.applid) {
			retval = -EEXIST;
			goto register_out;
		}
		if (copy_from_user(&cdev->ap.rparam, argp,
				   sizeof(struct capi_register_params))) {
			retval = -EFAULT;
			goto register_out;
		}
		cdev->ap.private = cdev;
		cdev->ap.recv_message = capi_recv_message;
		cdev->errcode = capi20_register(&cdev->ap);
		retval = (int)cdev->ap.applid;
		if (cdev->errcode) {
			cdev->ap.applid = 0;
			retval = -EIO;
		}

register_out:
		mutex_unlock(&cdev->lock);
		return retval;

	case CAPI_GET_VERSION:
		if (copy_from_user(&data.contr, argp,
				   sizeof(data.contr)))
			return -EFAULT;
		cdev->errcode = capi20_get_version(data.contr, &data.version);
		if (cdev->errcode)
			return -EIO;
		if (copy_to_user(argp, &data.version,
				 sizeof(data.version)))
			return -EFAULT;
		return 0;

	case CAPI_GET_SERIAL:
		if (copy_from_user(&data.contr, argp,
				   sizeof(data.contr)))
			return -EFAULT;
		cdev->errcode = capi20_get_serial(data.contr, data.serial);
		if (cdev->errcode)
			return -EIO;
		if (copy_to_user(argp, data.serial,
				 sizeof(data.serial)))
			return -EFAULT;
		return 0;

	case CAPI_GET_PROFILE:
		if (copy_from_user(&data.contr, argp,
				   sizeof(data.contr)))
			return -EFAULT;

		if (data.contr == 0) {
			cdev->errcode = capi20_get_profile(data.contr, &data.profile);
			if (cdev->errcode)
				return -EIO;

			retval = copy_to_user(argp,
					      &data.profile.ncontroller,
					      sizeof(data.profile.ncontroller));

		} else {
			cdev->errcode = capi20_get_profile(data.contr, &data.profile);
			if (cdev->errcode)
				return -EIO;

			retval = copy_to_user(argp, &data.profile,
					      sizeof(data.profile));
		}
		if (retval)
			return -EFAULT;
		return 0;

	case CAPI_GET_MANUFACTURER:
		if (copy_from_user(&data.contr, argp,
				   sizeof(data.contr)))
			return -EFAULT;
		cdev->errcode = capi20_get_manufacturer(data.contr, data.manufacturer);
		if (cdev->errcode)
			return -EIO;

		if (copy_to_user(argp, data.manufacturer,
				 sizeof(data.manufacturer)))
			return -EFAULT;

		return 0;

	case CAPI_GET_ERRCODE:
		data.errcode = cdev->errcode;
		cdev->errcode = CAPI_NOERROR;
		if (arg) {
			if (copy_to_user(argp, &data.errcode,
					 sizeof(data.errcode)))
				return -EFAULT;
		}
		return data.errcode;

	case CAPI_INSTALLED:
		if (capi20_isinstalled() == CAPI_NOERROR)
			return 0;
		return -ENXIO;

	case CAPI_MANUFACTURER_CMD: {
		struct capi_manufacturer_cmd mcmd;
		if (!capable(CAP_SYS_ADMIN))
			return -EPERM;
		if (copy_from_user(&mcmd, argp, sizeof(mcmd)))
			return -EFAULT;
		return capi20_manufacturer(mcmd.cmd, mcmd.data);
	}
	case CAPI_SET_FLAGS:
	case CAPI_CLR_FLAGS: {
		unsigned userflags;

		if (copy_from_user(&userflags, argp, sizeof(userflags)))
			return -EFAULT;

		mutex_lock(&cdev->lock);
		if (cmd == CAPI_SET_FLAGS)
			cdev->userflags |= userflags;
		else
			cdev->userflags &= ~userflags;
		mutex_unlock(&cdev->lock);
		return 0;
	}
	case CAPI_GET_FLAGS:
		if (copy_to_user(argp, &cdev->userflags,
				 sizeof(cdev->userflags)))
			return -EFAULT;
		return 0;

#ifndef CONFIG_ISDN_CAPI_MIDDLEWARE
	case CAPI_NCCI_OPENCOUNT:
		return 0;

#else /* CONFIG_ISDN_CAPI_MIDDLEWARE */
	case CAPI_NCCI_OPENCOUNT: {
		struct capincci *nccip;
		unsigned ncci;
		int count = 0;

		if (copy_from_user(&ncci, argp, sizeof(ncci)))
			return -EFAULT;

		mutex_lock(&cdev->lock);
		nccip = capincci_find(cdev, (u32)ncci);
		if (nccip)
			count = capincci_minor_opencount(nccip);
		mutex_unlock(&cdev->lock);
		return count;
	}

	case CAPI_NCCI_GETUNIT: {
		struct capincci *nccip;
		struct capiminor *mp;
		unsigned ncci;
		int unit = -ESRCH;

		if (copy_from_user(&ncci, argp, sizeof(ncci)))
			return -EFAULT;

		mutex_lock(&cdev->lock);
		nccip = capincci_find(cdev, (u32)ncci);
		if (nccip) {
			mp = nccip->minorp;
			if (mp)
				unit = mp->minor;
		}
		mutex_unlock(&cdev->lock);
		return unit;
	}
#endif /* CONFIG_ISDN_CAPI_MIDDLEWARE */

	default:
		return -EINVAL;
	}
