switch (cmd) {
	case USBDEVFS_CONTROL:
		snoop(&dev->dev, "%s: CONTROL\n", __func__);
		ret = proc_control(ps, p);
		if (ret >= 0)
			inode->i_mtime = CURRENT_TIME;
		break;

	case USBDEVFS_BULK:
		snoop(&dev->dev, "%s: BULK\n", __func__);
		ret = proc_bulk(ps, p);
		if (ret >= 0)
			inode->i_mtime = CURRENT_TIME;
		break;

	case USBDEVFS_RESETEP:
		snoop(&dev->dev, "%s: RESETEP\n", __func__);
		ret = proc_resetep(ps, p);
		if (ret >= 0)
			inode->i_mtime = CURRENT_TIME;
		break;

	case USBDEVFS_RESET:
		snoop(&dev->dev, "%s: RESET\n", __func__);
		ret = proc_resetdevice(ps);
		break;

	case USBDEVFS_CLEAR_HALT:
		snoop(&dev->dev, "%s: CLEAR_HALT\n", __func__);
		ret = proc_clearhalt(ps, p);
		if (ret >= 0)
			inode->i_mtime = CURRENT_TIME;
		break;

	case USBDEVFS_GETDRIVER:
		snoop(&dev->dev, "%s: GETDRIVER\n", __func__);
		ret = proc_getdriver(ps, p);
		break;

	case USBDEVFS_CONNECTINFO:
		snoop(&dev->dev, "%s: CONNECTINFO\n", __func__);
		ret = proc_connectinfo(ps, p);
		break;

	case USBDEVFS_SETINTERFACE:
		snoop(&dev->dev, "%s: SETINTERFACE\n", __func__);
		ret = proc_setintf(ps, p);
		break;

	case USBDEVFS_SETCONFIGURATION:
		snoop(&dev->dev, "%s: SETCONFIGURATION\n", __func__);
		ret = proc_setconfig(ps, p);
		break;

	case USBDEVFS_SUBMITURB:
		snoop(&dev->dev, "%s: SUBMITURB\n", __func__);
		ret = proc_submiturb(ps, p);
		if (ret >= 0)
			inode->i_mtime = CURRENT_TIME;
		break;

#ifdef CONFIG_COMPAT
	case USBDEVFS_CONTROL32:
		snoop(&dev->dev, "%s: CONTROL32\n", __func__);
		ret = proc_control_compat(ps, p);
		if (ret >= 0)
			inode->i_mtime = CURRENT_TIME;
		break;

	case USBDEVFS_BULK32:
		snoop(&dev->dev, "%s: BULK32\n", __func__);
		ret = proc_bulk_compat(ps, p);
		if (ret >= 0)
			inode->i_mtime = CURRENT_TIME;
		break;

	case USBDEVFS_DISCSIGNAL32:
		snoop(&dev->dev, "%s: DISCSIGNAL32\n", __func__);
		ret = proc_disconnectsignal_compat(ps, p);
		break;

	case USBDEVFS_SUBMITURB32:
		snoop(&dev->dev, "%s: SUBMITURB32\n", __func__);
		ret = proc_submiturb_compat(ps, p);
		if (ret >= 0)
			inode->i_mtime = CURRENT_TIME;
		break;

	case USBDEVFS_REAPURB32:
		snoop(&dev->dev, "%s: REAPURB32\n", __func__);
		ret = proc_reapurb_compat(ps, p);
		break;

	case USBDEVFS_REAPURBNDELAY32:
		snoop(&dev->dev, "%s: REAPURBNDELAY32\n", __func__);
		ret = proc_reapurbnonblock_compat(ps, p);
		break;

	case USBDEVFS_IOCTL32:
		snoop(&dev->dev, "%s: IOCTL32\n", __func__);
		ret = proc_ioctl_compat(ps, ptr_to_compat(p));
		break;
#endif

	case USBDEVFS_DISCARDURB:
		snoop(&dev->dev, "%s: DISCARDURB\n", __func__);
		ret = proc_unlinkurb(ps, p);
		break;

	case USBDEVFS_REAPURB:
		snoop(&dev->dev, "%s: REAPURB\n", __func__);
		ret = proc_reapurb(ps, p);
		break;

	case USBDEVFS_REAPURBNDELAY:
		snoop(&dev->dev, "%s: REAPURBNDELAY\n", __func__);
		ret = proc_reapurbnonblock(ps, p);
		break;

	case USBDEVFS_DISCSIGNAL:
		snoop(&dev->dev, "%s: DISCSIGNAL\n", __func__);
		ret = proc_disconnectsignal(ps, p);
		break;

	case USBDEVFS_CLAIMINTERFACE:
		snoop(&dev->dev, "%s: CLAIMINTERFACE\n", __func__);
		ret = proc_claiminterface(ps, p);
		break;

	case USBDEVFS_RELEASEINTERFACE:
		snoop(&dev->dev, "%s: RELEASEINTERFACE\n", __func__);
		ret = proc_releaseinterface(ps, p);
		break;

	case USBDEVFS_IOCTL:
		snoop(&dev->dev, "%s: IOCTL\n", __func__);
		ret = proc_ioctl_default(ps, p);
		break;

	case USBDEVFS_CLAIM_PORT:
		snoop(&dev->dev, "%s: CLAIM_PORT\n", __func__);
		ret = proc_claim_port(ps, p);
		break;

	case USBDEVFS_RELEASE_PORT:
		snoop(&dev->dev, "%s: RELEASE_PORT\n", __func__);
		ret = proc_release_port(ps, p);
		break;
	case USBDEVFS_GET_CAPABILITIES:
		ret = proc_get_capabilities(ps, p);
		break;
	case USBDEVFS_DISCONNECT_CLAIM:
		ret = proc_disconnect_claim(ps, p);
		break;
	}
