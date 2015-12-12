switch (cmd) {
	case FBIOGET_VBLANK: {
		struct fb_vblank vblank = {0};
		void __user *argp = (void __user *) arg;

		tmiofb_vblank(fbi, &vblank);
		if (copy_to_user(argp, &vblank, sizeof vblank))
			return -EFAULT;
		return 0;
	}

#ifdef CONFIG_FB_TMIO_ACCELL
	case FBIO_TMIO_ACC_SYNC:
		tmiofb_sync(fbi);
		return 0;

	case FBIO_TMIO_ACC_WRITE: {
		u32 __user *argp = (void __user *) arg;
		u32 len;
		u32 acc[16];

		if (get_user(len, argp))
			return -EFAULT;
		if (len > ARRAY_SIZE(acc))
			return -EINVAL;
		if (copy_from_user(acc, argp + 1, sizeof(u32) * len))
			return -EFAULT;

		return tmiofb_acc_write(fbi, acc, len);
	}
#endif
	}
