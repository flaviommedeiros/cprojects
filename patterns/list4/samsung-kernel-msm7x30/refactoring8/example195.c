static struct of_device_id fsl_diu_match[] = {
#ifdef CONFIG_PPC_MPC512x
	{
		.compatible = "fsl,mpc5121-diu",
	},
#endif
	{
		.compatible = "fsl,diu",
	},
	{}
};
