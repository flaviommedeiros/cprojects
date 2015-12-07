#ifdef CONFIG_COMPAT
if (cmd == NCP_IOC_SETPRIVATEDATA_32) {
				struct compat_ncp_privatedata_ioctl user32;
				if (copy_from_user(&user32, argp, sizeof(user32)))
					return -EFAULT;
				user.len = user32.len;
				user.data = compat_ptr(user32.data);
			} else
#endif
			if (copy_from_user(&user, argp, sizeof(user)))
				return -EFAULT;
