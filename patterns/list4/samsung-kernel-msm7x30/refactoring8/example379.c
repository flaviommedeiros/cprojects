static struct msm_camera_sensor_info msm_camera_sensor_imx111_data = {
	.sensor_name	= "imx111",
	.pdata	= &msm_camera_csi_device_data[0],
	.flash_data	= &flash_imx111,
	.sensor_platform_info = &sensor_board_info_imx111,
	.csi_if	= 1,
	.camera_type = BACK_CAMERA_2D,
	.sensor_type = BAYER_SENSOR,
#ifdef CONFIG_SEKONIX_LENS_ACT
	.actuator_info = &msm_act_main_cam_0_info,

#endif
};
