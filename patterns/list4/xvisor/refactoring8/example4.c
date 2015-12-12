static struct platform_device_id fec_devtype[] = {
	{
		/* keep it for coldfire */
		.name = DRIVER_NAME,
		.driver_data = 0,
	}, {
		.name = "imx25-fec",
		.driver_data = FEC_QUIRK_USE_GASKET,
	}, {
		.name = "imx27-fec",
		.driver_data = 0,
	}, {
		.name = "imx28-fec",
		.driver_data = FEC_QUIRK_ENET_MAC | FEC_QUIRK_SWAP_FRAME,
	}, {
		.name = "imx6q-fec",
#if 0
		.driver_data = FEC_QUIRK_ENET_MAC | FEC_QUIRK_HAS_GBIT |
				FEC_QUIRK_HAS_BUFDESC_EX | FEC_QUIRK_HAS_CSUM |
				FEC_QUIRK_HAS_VLAN | FEC_QUIRK_ERR006358,
#else /* 0 */
		/* FIXME: TEMPORARY */
		.driver_data = FEC_QUIRK_ENET_MAC | FEC_QUIRK_HAS_GBIT |
				FEC_QUIRK_HAS_CSUM |
				FEC_QUIRK_HAS_VLAN | FEC_QUIRK_ERR006358,
#endif /* 0 */
	}, {
		.name = "mvf600-fec",
		.driver_data = FEC_QUIRK_ENET_MAC,
	}, {
		.name = "imx6sx-fec",
		.driver_data = FEC_QUIRK_ENET_MAC | FEC_QUIRK_HAS_GBIT |
				FEC_QUIRK_HAS_BUFDESC_EX | FEC_QUIRK_HAS_CSUM |
				FEC_QUIRK_HAS_VLAN | FEC_QUIRK_HAS_AVB |
				FEC_QUIRK_ERR007885 | FEC_QUIRK_BUG_CAPTURE,
	}, {
		/* sentinel */
	}
};
