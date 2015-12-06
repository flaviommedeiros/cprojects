static RFSPartitionType partitions[] = {
	/* LGPL code */
	{ "dos", &fs_part_dos, fs_parhook },
#if USE_GRUB
	/* WARNING GPL code */
	{ "msdos", (void*)&grub_msdos_partition_map, (void*)grub_parhook },
	{ "apple", &grub_apple_partition_map },
	{ "sun", &grub_sun_partition_map },
	{ "sunpc", &grub_sun_pc_partition_map },
	{ "amiga", &grub_amiga_partition_map },
	{ "bsdlabel", &grub_bsdlabel_partition_map },
	{ "gpt", &grub_gpt_partition_map },
#endif
// XXX: In BURG all bsd partition map are in bsdlabel
	//{ "openbsdlabel", &grub_openbsd_partition_map },
	//{ "netbsdlabel", &grub_netbsd_partition_map },
	//{ "acorn", &grub_acorn_partition_map },
	{ NULL }
};
