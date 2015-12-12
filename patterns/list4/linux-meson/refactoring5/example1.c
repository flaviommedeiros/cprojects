#ifdef CONFIG_COMPAT
if (unlikely(is_compat_task())) {
			compat_siginfo_t __user *uinfo = compat_ptr(data);

			if (copy_siginfo_to_user32(uinfo, &info) ||
			    __put_user(info.si_code, &uinfo->si_code)) {
				ret = -EFAULT;
				break;
			}

		} else
#endif
		{
			siginfo_t __user *uinfo = (siginfo_t __user *) data;

			if (copy_siginfo_to_user(uinfo, &info) ||
			    __put_user(info.si_code, &uinfo->si_code)) {
				ret = -EFAULT;
				break;
			}
		}
