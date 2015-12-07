#ifdef CONFIG_COMPAT
if (cmd == NCP_IOC_NCPREQUEST_32) {
			struct compat_ncp_ioctl_request request32;
			if (copy_from_user(&request32, argp, sizeof(request32)))
				return -EFAULT;
			request.function = request32.function;
			request.size = request32.size;
			request.data = compat_ptr(request32.data);
		} else
#endif
		if (copy_from_user(&request, argp, sizeof(request)))
			return -EFAULT;
