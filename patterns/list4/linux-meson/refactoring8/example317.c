static const struct of_device_id fsl_of_msi_ids[] = {
	{
		.compatible = "fsl,mpic-msi",
		.data = &mpic_msi_feature,
	},
	{
		.compatible = "fsl,ipic-msi",
		.data = &ipic_msi_feature,
	},
#ifdef CONFIG_EPAPR_PARAVIRT
	{
		.compatible = "fsl,vmpic-msi",
		.data = &vmpic_msi_feature,
	},
#endif
	{}
};
