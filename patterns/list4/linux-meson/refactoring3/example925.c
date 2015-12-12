switch (cmd) {
#ifdef FBCMD_GET_CURRENTPAR
	case FBCMD_GET_CURRENTPAR:
		if (copy_to_user((void *)arg, (void *)&current_par,
				 sizeof(struct atafb_par)))
			return -EFAULT;
		return 0;
#endif
#ifdef FBCMD_SET_CURRENTPAR
	case FBCMD_SET_CURRENTPAR:
		if (copy_from_user((void *)&current_par, (void *)arg,
				   sizeof(struct atafb_par)))
			return -EFAULT;
		ata_set_par(&current_par);
		return 0;
#endif
	}
