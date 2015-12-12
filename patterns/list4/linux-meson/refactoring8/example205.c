static struct drm_info_list radeon_ttm_debugfs_list[] = {
	{"radeon_vram_mm", radeon_mm_dump_table, 0, &ttm_pl_vram},
	{"radeon_gtt_mm", radeon_mm_dump_table, 0, &ttm_pl_tt},
	{"ttm_page_pool", ttm_page_alloc_debugfs, 0, NULL},
#ifdef CONFIG_SWIOTLB
	{"ttm_dma_page_pool", ttm_dma_page_alloc_debugfs, 0, NULL}
#endif
};
