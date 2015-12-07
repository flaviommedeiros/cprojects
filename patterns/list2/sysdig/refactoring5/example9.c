#ifdef CONFIG_COMPAT
if (!args->compat) {
#endif
			if (unlikely(ppm_copy_from_user(&rl, (const void __user *)val, sizeof(struct rlimit)))) {
				newcur = -1;
				newmax = -1;
			} else {
				newcur = rl.rlim_cur;
				newmax = rl.rlim_max;
			}
#ifdef CONFIG_COMPAT
		} else {
			if (unlikely(ppm_copy_from_user(&compat_rl, (const void __user *)val, sizeof(struct compat_rlimit)))) {
				newcur = -1;
				newmax = -1;
			} else {
				newcur = compat_rl.rlim_cur;
				newmax = compat_rl.rlim_max;
			}
		}
