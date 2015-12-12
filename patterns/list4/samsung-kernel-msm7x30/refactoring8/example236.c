static struct mtd_partition higlvl_partition_info[]=
{
	{
		.name =		"ADNP boot block",
		.offset =	0,
		.size =		CONFIG_MTD_DILNETPC_BOOTSIZE,
	},
	{
		.name =		"ADNP file system space",
		.offset =	MTDPART_OFS_NXTBLK,
		.size =		ADNP_WINDOW_SIZE-CONFIG_MTD_DILNETPC_BOOTSIZE-0x20000,
	},
	{
		.name =		"ADNP system BIOS + BIOS Entry",
		.offset =	MTDPART_OFS_NXTBLK,
		.size =		MTDPART_SIZ_FULL,
#ifdef DNPC_BIOS_BLOCKS_WRITEPROTECTED
		.mask_flags =	MTD_WRITEABLE,
#endif
	},
};
