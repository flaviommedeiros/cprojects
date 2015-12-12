static struct platform_device *ixdp425_devices[] __initdata = {
	&ixdp425_i2c_gpio,
	&ixdp425_flash,
#if defined(CONFIG_MTD_NAND_PLATFORM) || \
    defined(CONFIG_MTD_NAND_PLATFORM_MODULE)
	&ixdp425_flash_nand,
#endif
	&ixdp425_uart,
	&ixdp425_eth[0],
	&ixdp425_eth[1],
};
