static struct amba_device *amba_devs[] __initdata = {
	&uart0_device,
#ifdef CONFIG_MACH_U300_BS335
	&uart1_device,
#endif
	&pl022_device,
	&pl172_device,
	&mmcsd_device,
};
