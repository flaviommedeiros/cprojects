static struct mtd_partition __initdata jive_imageB_nand_part[] = {

#ifdef CONFIG_MACH_JIVE_SHOW_BOOTLOADER
	/* Don't allow access to the bootloader from linux */
	{
		.name           = "uboot",
		.offset         = 0,
		.size           = (160 * SZ_1K),
		.mask_flags	= MTD_WRITEABLE, /* force read-only */
	},

	/* spare */
        {
                .name           = "spare",
                .offset         = (176 * SZ_1K),
                .size           = (16 * SZ_1K),
        },
#endif

	/* booted images */
        {
		.name           = "kernel (ro)",
		.offset         = (22 * SZ_1M),
		.size           = (2 * SZ_1M) - (192 * SZ_1K),
		.mask_flags	= MTD_WRITEABLE, /* force read-only */
        },
	{
		.name		= "root (ro)",
		.offset		= (24 * SZ_1M) - (192 * SZ_1K),
                .size		= (20 * SZ_1M),
		.mask_flags	= MTD_WRITEABLE, /* force read-only */
	},

	/* yaffs */
	{
		.name		= "yaffs",
		.offset		= (44 * SZ_1M),
		.size		= (20 * SZ_1M),
        },

	/* bootloader environment */
	{
		.name		= "env",
		.offset		= (160 * SZ_1K),
		.size		= (16 * SZ_1K),
	},

	/* upgrade images */
	{
		.name		= "zimage",
		.offset		= (192 * SZ_1K),
		.size		= (2 * SZ_1M) - (192 * SZ_1K),
        }, {
		.name		= "cramfs",
		.offset		= (2 * SZ_1M),
		.size		= (20 * SZ_1M),
        },
};