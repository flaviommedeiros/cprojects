switch (cmd) {
	case HDIO_OBSOLETE_IDENTITY:
	case HDIO_GET_IDENTITY:
		if (bdev != bdev->bd_contains)
			return -EINVAL;
		return ide_get_identity_ioctl(drive, cmd, arg);
	case HDIO_GET_NICE:
		return ide_get_nice_ioctl(drive, arg);
	case HDIO_SET_NICE:
		if (!capable(CAP_SYS_ADMIN))
			return -EACCES;
		return ide_set_nice_ioctl(drive, arg);
#ifdef CONFIG_IDE_TASK_IOCTL
	case HDIO_DRIVE_TASKFILE:
		if (!capable(CAP_SYS_ADMIN) || !capable(CAP_SYS_RAWIO))
			return -EACCES;
		if (drive->media == ide_disk)
			return ide_taskfile_ioctl(drive, arg);
		return -ENOMSG;
#endif
	case HDIO_DRIVE_CMD:
		if (!capable(CAP_SYS_RAWIO))
			return -EACCES;
		return ide_cmd_ioctl(drive, arg);
	case HDIO_DRIVE_TASK:
		if (!capable(CAP_SYS_RAWIO))
			return -EACCES;
		return ide_task_ioctl(drive, arg);
	case HDIO_DRIVE_RESET:
		if (!capable(CAP_SYS_ADMIN))
			return -EACCES;
		return generic_drive_reset(drive);
	case HDIO_GET_BUSSTATE:
		if (!capable(CAP_SYS_ADMIN))
			return -EACCES;
		if (put_user(BUSSTATE_ON, (long __user *)arg))
			return -EFAULT;
		return 0;
	case HDIO_SET_BUSSTATE:
		if (!capable(CAP_SYS_ADMIN))
			return -EACCES;
		return -EOPNOTSUPP;
	default:
		return -EINVAL;
	}
