static const struct of_device_id fs_enet_mdio_fec_match[] = {
	{
		.compatible = "fsl,pq1-fec-mdio",
	},
#if defined(CONFIG_PPC_MPC512x)
	{
		.compatible = "fsl,mpc5121-fec-mdio",
		.data = mpc5xxx_get_bus_frequency,
	},
#endif
	{},
};
