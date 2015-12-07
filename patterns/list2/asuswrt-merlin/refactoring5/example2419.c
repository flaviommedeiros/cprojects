#ifdef CONFIG_COMPAT
if (cmd == NCP_IOC_SETOBJECTNAME_32) {
				struct compat_ncp_objectname_ioctl user32;
				if (copy_from_user(&user32, argp, sizeof(user32)))
					return -EFAULT;
				user.auth_type = user32.auth_type;
				user.object_name_len = user32.object_name_len;
				user.object_name = compat_ptr(user32.object_name);
			} else
#endif
			if (copy_from_user(&user, argp, sizeof(user)))
				return -EFAULT;
