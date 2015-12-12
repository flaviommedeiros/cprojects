static struct msm_usb_bam_platform_data msm_usb_bam_pdata = {
	.connections = &msm_usb_bam_connections[0][0][0],
#ifndef CONFIG_USB_CI13XXX_MSM_HSIC
	.usb_active_bam = HSUSB_BAM,
#else
	.usb_active_bam = HSIC_BAM,
#endif
	.usb_bam_num_pipes = 16,
};
