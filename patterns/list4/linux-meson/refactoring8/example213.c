static const struct of_device_id fsl_usb2_mph_dr_of_match[] = {
	{ .compatible = "fsl-usb2-mph", .data = &fsl_usb2_mpc8xxx_pd, },
	{ .compatible = "fsl-usb2-dr", .data = &fsl_usb2_mpc8xxx_pd, },
#ifdef CONFIG_PPC_MPC512x
	{ .compatible = "fsl,mpc5121-usb2-dr", .data = &fsl_usb2_mpc5121_pd, },
#endif
	{},
};
