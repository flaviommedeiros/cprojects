switch (cmd) {
	case MPT2IOCINFO:
		if (_IOC_SIZE(cmd) == sizeof(struct mpt2_ioctl_iocinfo))
			ret = _ctl_getiocinfo(ioc, arg);
		break;
#ifdef CONFIG_COMPAT
	case MPT2COMMAND32:
#endif
	case MPT2COMMAND:
	{
		struct mpt2_ioctl_command __user *uarg;
		struct mpt2_ioctl_command karg;
#ifdef CONFIG_COMPAT
		if (compat) {
			ret = _ctl_compat_mpt_command(ioc, cmd, arg);
			break;
		}
#endif
		if (copy_from_user(&karg, arg, sizeof(karg))) {
			printk(KERN_ERR "failure at %s:%d/%s()!\n",
			    __FILE__, __LINE__, __func__);
			ret = -EFAULT;
			break;
		}

		if (_IOC_SIZE(cmd) == sizeof(struct mpt2_ioctl_command)) {
			uarg = arg;
			ret = _ctl_do_mpt_command(ioc, karg, &uarg->mf);
		}
		break;
	}
	case MPT2EVENTQUERY:
		if (_IOC_SIZE(cmd) == sizeof(struct mpt2_ioctl_eventquery))
			ret = _ctl_eventquery(ioc, arg);
		break;
	case MPT2EVENTENABLE:
		if (_IOC_SIZE(cmd) == sizeof(struct mpt2_ioctl_eventenable))
			ret = _ctl_eventenable(ioc, arg);
		break;
	case MPT2EVENTREPORT:
		ret = _ctl_eventreport(ioc, arg);
		break;
	case MPT2HARDRESET:
		if (_IOC_SIZE(cmd) == sizeof(struct mpt2_ioctl_diag_reset))
			ret = _ctl_do_reset(ioc, arg);
		break;
	case MPT2BTDHMAPPING:
		if (_IOC_SIZE(cmd) == sizeof(struct mpt2_ioctl_btdh_mapping))
			ret = _ctl_btdh_mapping(ioc, arg);
		break;
	case MPT2DIAGREGISTER:
		if (_IOC_SIZE(cmd) == sizeof(struct mpt2_diag_register))
			ret = _ctl_diag_register(ioc, arg);
		break;
	case MPT2DIAGUNREGISTER:
		if (_IOC_SIZE(cmd) == sizeof(struct mpt2_diag_unregister))
			ret = _ctl_diag_unregister(ioc, arg);
		break;
	case MPT2DIAGQUERY:
		if (_IOC_SIZE(cmd) == sizeof(struct mpt2_diag_query))
			ret = _ctl_diag_query(ioc, arg);
		break;
	case MPT2DIAGRELEASE:
		if (_IOC_SIZE(cmd) == sizeof(struct mpt2_diag_release))
			ret = _ctl_diag_release(ioc, arg);
		break;
	case MPT2DIAGREADBUFFER:
		if (_IOC_SIZE(cmd) == sizeof(struct mpt2_diag_read_buffer))
			ret = _ctl_diag_read_buffer(ioc, arg);
		break;
	default:

		dctlprintk(ioc, printk(MPT2SAS_INFO_FMT
		    "unsupported ioctl opcode(0x%08x)\n", ioc->name, cmd));
		break;
	}
