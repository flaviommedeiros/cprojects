static struct atmel_ssc_info ssc_info[NUM_SSC_DEVICES] = {
	{
	.name		= "ssc0",
	.lock		= __SPIN_LOCK_UNLOCKED(ssc_info[0].lock),
	.dir_mask	= SSC_DIR_MASK_UNUSED,
	.initialized	= 0,
	},
#if NUM_SSC_DEVICES == 3
	{
	.name		= "ssc1",
	.lock		= __SPIN_LOCK_UNLOCKED(ssc_info[1].lock),
	.dir_mask	= SSC_DIR_MASK_UNUSED,
	.initialized	= 0,
	},
	{
	.name		= "ssc2",
	.lock		= __SPIN_LOCK_UNLOCKED(ssc_info[2].lock),
	.dir_mask	= SSC_DIR_MASK_UNUSED,
	.initialized	= 0,
	},
#endif
};
