switch(cmd){
	case FDFMTBEG:
		get_fdc(drive);
		if (fd_ref[drive] > 1) {
			rel_fdc();
			return -EBUSY;
		}
		fsync_bdev(bdev);
		if (fd_motor_on(drive) == 0) {
			rel_fdc();
			return -ENODEV;
		}
		if (fd_calibrate(drive) == 0) {
			rel_fdc();
			return -ENXIO;
		}
		floppy_off(drive);
		rel_fdc();
		break;
	case FDFMTTRK:
		if (param < p->type->tracks * p->type->heads)
		{
			get_fdc(drive);
			if (fd_seek(drive,param) != 0){
				memset(p->trackbuf, FD_FILL_BYTE,
				       p->dtype->sects * p->type->sect_mult * 512);
				non_int_flush_track(drive);
			}
			floppy_off(drive);
			rel_fdc();
		}
		else
			return -EINVAL;
		break;
	case FDFMTEND:
		floppy_off(drive);
		invalidate_bdev(bdev);
		break;
	case FDGETPRM:
		memset((void *)&getprm, 0, sizeof (getprm));
		getprm.track=p->type->tracks;
		getprm.head=p->type->heads;
		getprm.sect=p->dtype->sects * p->type->sect_mult;
		getprm.size=p->blocks;
		if (copy_to_user(argp, &getprm, sizeof(struct floppy_struct)))
			return -EFAULT;
		break;
	case FDSETPRM:
	case FDDEFPRM:
		return -EINVAL;
	case FDFLUSH: /* unconditionally, even if not needed */
		del_timer (flush_track_timer + drive);
		non_int_flush_track(drive);
		break;
#ifdef RAW_IOCTL
	case IOCTL_RAW_TRACK:
		if (copy_to_user(argp, raw_buf, p->type->read_size))
			return -EFAULT;
		else
			return p->type->read_size;
#endif
	default:
		printk(KERN_DEBUG "fd_ioctl: unknown cmd %d for drive %d.",
		       cmd, drive);
		return -ENOSYS;
	}
