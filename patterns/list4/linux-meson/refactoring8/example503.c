static struct platform_device *pnx833x_platform_devices[] __initdata = {
	&pnx833x_uart_device,
	&pnx833x_usb_ehci_device,
#ifdef CONFIG_I2C_PNX0105
	&pnx833x_i2c0_device,
	&pnx833x_i2c1_device,
#endif
	&pnx833x_ethernet_device,
	&pnx833x_sata_device,
	&pnx833x_flash_nand,
};
