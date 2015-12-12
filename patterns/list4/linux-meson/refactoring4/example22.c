#if (LINUX_VERSION_CODE>=KERNEL_VERSION(2,6,29))
if (dev->netdev_ops->ndo_do_ioctl != rtw_ioctl)
#else
	if (dev->do_ioctl != rtw_ioctl)
#endif
		return NOTIFY_DONE;
