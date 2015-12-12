static struct agp_device_ids via_agp_device_ids[] __devinitdata =
{
	{
		.device_id	= PCI_DEVICE_ID_VIA_82C597_0,
		.chipset_name	= "Apollo VP3",
	},

	{
		.device_id	= PCI_DEVICE_ID_VIA_82C598_0,
		.chipset_name	= "Apollo MVP3",
	},

	{
		.device_id	= PCI_DEVICE_ID_VIA_8501_0,
		.chipset_name	= "Apollo MVP4",
	},

	/* VT8601 */
	{
		.device_id	= PCI_DEVICE_ID_VIA_8601_0,
		.chipset_name	= "Apollo ProMedia/PLE133Ta",
	},

	/* VT82C693A / VT28C694T */
	{
		.device_id	= PCI_DEVICE_ID_VIA_82C691_0,
		.chipset_name	= "Apollo Pro 133",
	},

	{
		.device_id	= PCI_DEVICE_ID_VIA_8371_0,
		.chipset_name	= "KX133",
	},

	/* VT8633 */
	{
		.device_id	= PCI_DEVICE_ID_VIA_8633_0,
		.chipset_name	= "Pro 266",
	},

	{
		.device_id	= PCI_DEVICE_ID_VIA_XN266,
		.chipset_name	= "Apollo Pro266",
	},

	/* VT8361 */
	{
		.device_id	= PCI_DEVICE_ID_VIA_8361,
		.chipset_name	= "KLE133",
	},

	/* VT8365 / VT8362 */
	{
		.device_id	= PCI_DEVICE_ID_VIA_8363_0,
		.chipset_name	= "Twister-K/KT133x/KM133",
	},

	/* VT8753A */
	{
		.device_id	= PCI_DEVICE_ID_VIA_8753_0,
		.chipset_name	= "P4X266",
	},

	/* VT8366 */
	{
		.device_id	= PCI_DEVICE_ID_VIA_8367_0,
		.chipset_name	= "KT266/KY266x/KT333",
	},

	/* VT8633 (for CuMine/ Celeron) */
	{
		.device_id	= PCI_DEVICE_ID_VIA_8653_0,
		.chipset_name	= "Pro266T",
	},

	/* KM266 / PM266 */
	{
		.device_id	= PCI_DEVICE_ID_VIA_XM266,
		.chipset_name	= "PM266/KM266",
	},

	/* CLE266 */
	{
		.device_id	= PCI_DEVICE_ID_VIA_862X_0,
		.chipset_name	= "CLE266",
	},

	{
		.device_id	= PCI_DEVICE_ID_VIA_8377_0,
		.chipset_name	= "KT400/KT400A/KT600",
	},

	/* VT8604 / VT8605 / VT8603
	 * (Apollo Pro133A chipset with S3 Savage4) */
	{
		.device_id	= PCI_DEVICE_ID_VIA_8605_0,
		.chipset_name	= "ProSavage PM133/PL133/PN133"
	},

	/* P4M266x/P4N266 */
	{
		.device_id	= PCI_DEVICE_ID_VIA_8703_51_0,
		.chipset_name	= "P4M266x/P4N266",
	},

	/* VT8754 */
	{
		.device_id	= PCI_DEVICE_ID_VIA_8754C_0,
		.chipset_name	= "PT800",
	},

	/* P4X600 */
	{
		.device_id	= PCI_DEVICE_ID_VIA_8763_0,
		.chipset_name	= "P4X600"
	},

	/* KM400 */
	{
		.device_id	= PCI_DEVICE_ID_VIA_8378_0,
		.chipset_name	= "KM400/KM400A",
	},

	/* PT880 */
	{
		.device_id	= PCI_DEVICE_ID_VIA_PT880,
		.chipset_name	= "PT880",
	},

	/* PT880 Ultra */
	{
		.device_id	= PCI_DEVICE_ID_VIA_PT880ULTRA,
		.chipset_name	= "PT880 Ultra",
	},

	/* PT890 */
	{
		.device_id	= PCI_DEVICE_ID_VIA_8783_0,
		.chipset_name	= "PT890",
	},

	/* PM800/PN800/PM880/PN880 */
	{
		.device_id	= PCI_DEVICE_ID_VIA_PX8X0_0,
		.chipset_name	= "PM800/PN800/PM880/PN880",
	},
	/* KT880 */
	{
		.device_id	= PCI_DEVICE_ID_VIA_3269_0,
		.chipset_name	= "KT880",
	},
	/* KTxxx/Px8xx */
	{
		.device_id	= PCI_DEVICE_ID_VIA_83_87XX_1,
		.chipset_name	= "VT83xx/VT87xx/KTxxx/Px8xx",
	},
	/* P4M800 */
	{
		.device_id	= PCI_DEVICE_ID_VIA_3296_0,
		.chipset_name	= "P4M800",
	},
	/* P4M800CE */
	{
		.device_id	= PCI_DEVICE_ID_VIA_P4M800CE,
		.chipset_name	= "VT3314",
	},
	/* VT3324 / CX700 */
	{
		.device_id  = PCI_DEVICE_ID_VIA_VT3324,
		.chipset_name   = "CX700",
	},
	/* VT3336 - this is a chipset for AMD Athlon/K8 CPU. Due to K8's unique
	 * architecture, the AGP resource and behavior are different from
	 * the traditional AGP which resides only in chipset. AGP is used
	 * by 3D driver which wasn't available for the VT3336 and VT3364
	 * generation until now.  Unfortunately, by testing, VT3364 works
	 * but VT3336 doesn't. - explaination from via, just leave this as
	 * as a placeholder to avoid future patches adding it back in.
	 */
#if 0
	{
		.device_id  = PCI_DEVICE_ID_VIA_VT3336,
		.chipset_name   = "VT3336",
	},
#endif
	/* P4M890 */
	{
		.device_id  = PCI_DEVICE_ID_VIA_P4M890,
		.chipset_name   = "P4M890",
	},
	/* P4M900 */
	{
		.device_id  = PCI_DEVICE_ID_VIA_VT3364,
		.chipset_name   = "P4M900",
	},
	{ }, /* dummy final entry, always present */
};
