static struct zcomp_backend *backends[] = {
	&zcomp_lzo,
#ifdef CONFIG_ZRAM_LZ4_COMPRESS
	&zcomp_lz4,
#endif
	NULL
};
