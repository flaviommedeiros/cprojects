#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 0)
if ((gpio_major = register_chrdev(0, "gpio", &gpio_fops)) < 0)
#else
	if ((gpio_major = devfs_register_chrdev(0, "gpio", &gpio_fops)) < 0)
#endif
		return gpio_major;
