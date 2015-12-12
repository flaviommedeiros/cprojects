switch (cmd) {
	case MPT3IOCINFO:
		if (_IOC_SIZE(cmd) == sizeof(struct mpt3_ioctl_iocinfo))
			ret = _ctl_getiocinfo(ioc, arg);
		break;
#ifdef CONFIG_COMPAT
	case MPT3COMMAND32:
#endif
	case MPT3COMMAND:
	{
		struct mpt3_ioctl_command __user *uarg;
		struct mpt3_ioctl_command karg;

#ifdef CONFIG_COMPAT
		if (compat) {
			ret = _ctl_compat_mpt_command(ioc, cmd, arg);
			break;
		}
#endif
		if (copy_from_user(&karg, arg, sizeof(karg))) {
			pr_err("failure at %s:%d/%s()!\n",
			    __FILE__, __LINE__, __func__);
			ret = -EFAULT;
			break;
		}

		if (_IOC_SIZE(cmd) == sizeof(struct mpt3_ioctl_command)) {
			uarg = arg;
			ret = _ctl_do_mpt_command(ioc, karg, &uarg->mf);
		}
		break;
	}
	case MPT3EVENTQUERY:
		if (_IOC_SIZE(cmd) == sizeof(struct mpt3_ioctl_eventquery))
			ret = _ctl_eventquery(ioc, arg);
		break;
	case MPT3EVENTENABLE:
		if (_IOC_SIZE(cmd) == sizeof(struct mpt3_ioctl_eventenable))
			ret = _ctl_eventenable(ioc, arg);
		break;
	case MPT3EVENTREPORT:
		ret = _ctl_eventreport(ioc, arg);
		break;
	case MPT3HARDRESET:
		if (_IOC_SIZE(cmd) == sizeof(struct mpt3_ioctl_diag_reset))
			ret = _ctl_do_reset(ioc, arg);
		break;
	case MPT3BTDHMAPPING:
		if (_IOC_SIZE(cmd) == sizeof(struct mpt3_ioctl_btdh_mapping))
			ret = _ctl_btdh_mapping(ioc, arg);
		break;
	case MPT3DIAGREGISTER:
		if (_IOC_SIZE(cmd) == sizeof(struct mpt3_diag_register))
			ret = _ctl_diag_register(ioc, arg);
		break;
	case MPT3DIAGUNREGISTER:
		if (_IOC_SIZE(cmd) == sizeof(struct mpt3_diag_unregister))
			ret = _ctl_diag_unregister(ioc, arg);
		break;
	case MPT3DIAGQUERY:
		if (_IOC_SIZE(cmd) == sizeof(struct mpt3_diag_query))
			ret = _ctl_diag_query(ioc, arg);
		break;
	case MPT3DIAGRELEASE:
		if (_IOC_SIZE(cmd) == sizeof(struct mpt3_diag_release))
			ret = _ctl_diag_release(ioc, arg);
		break;
	case MPT3DIAGREADBUFFER:
		if (_IOC_SIZE(cmd) == sizeof(struct mpt3_diag_read_buffer))
			ret = _ctl_diag_read_buffer(ioc, arg);
		break;
	default:
		dctlprintk(ioc, pr_info(MPT3SAS_FMT
		    "unsupported ioctl opcode(0x%08x)\n", ioc->name, cmd));
		break;
	}
