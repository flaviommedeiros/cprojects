static struct msi2500_format formats[] = {
	{
		.name		= "Complex S8",
		.pixelformat	= V4L2_SDR_FMT_CS8,
		.buffersize	= 3 * 1008,
#if 0
	}, {
		.name		= "10+2-bit signed",
		.pixelformat	= MSI2500_PIX_FMT_SDR_MSI2500_384,
	}, {
		.name		= "12-bit signed",
		.pixelformat	= MSI2500_PIX_FMT_SDR_S12,
#endif
	}, {
		.name		= "Complex S14LE",
		.pixelformat	= V4L2_SDR_FMT_CS14LE,
		.buffersize	= 3 * 1008,
	}, {
		.name		= "Complex U8 (emulated)",
		.pixelformat	= V4L2_SDR_FMT_CU8,
		.buffersize	= 3 * 1008,
	}, {
		.name		= "Complex U16LE (emulated)",
		.pixelformat	=  V4L2_SDR_FMT_CU16LE,
		.buffersize	= 3 * 1008,
	},
};
