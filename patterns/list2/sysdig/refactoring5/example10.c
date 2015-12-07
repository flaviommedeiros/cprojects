#ifdef CONFIG_COMPAT
if (!args->compat) {
#endif
		if (unlikely(ppm_copy_from_user(&rl, (const void __user *)val, sizeof(struct rlimit)))) {
			oldcur = -1;
			oldmax = -1;
		} else {
			oldcur = rl.rlim_cur;
			oldmax = rl.rlim_max;
		}
#ifdef CONFIG_COMPAT
	} else {
		if (unlikely(ppm_copy_from_user(&compat_rl, (const void __user *)val, sizeof(struct compat_rlimit)))) {
			oldcur = -1;
			oldmax = -1;
		} else {
			oldcur = compat_rl.rlim_cur;
			oldmax = compat_rl.rlim_max;
		}
	}
