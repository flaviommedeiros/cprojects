if (S_ISBLK(sb.st_mode) && sysfs_devno_is_lvm_private(sb.st_rdev)) {
		DBG(LOWPROBE, ul_debug("ignore private LVM device"));
		pr->flags |= BLKID_FL_NOSCAN_DEV;
	}

#ifdef CDROM_GET_CAPABILITY
	else if (S_ISBLK(sb.st_mode) &&
	    !blkid_probe_is_tiny(pr) &&
	    blkid_probe_is_wholedisk(pr) &&
	    ioctl(fd, CDROM_GET_CAPABILITY, NULL) >= 0)
		pr->flags |= BLKID_FL_CDROM_DEV;
#endif
