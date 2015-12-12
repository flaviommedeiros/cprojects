static struct drm_info_list drm_debugfs_list[] = {
	{"name", drm_name_info, 0},
	{"vm", drm_vm_info, 0},
	{"clients", drm_clients_info, 0},
	{"queues", drm_queues_info, 0},
	{"bufs", drm_bufs_info, 0},
	{"gem_names", drm_gem_name_info, DRIVER_GEM},
#if DRM_DEBUG_CODE
	{"vma", drm_vma_info, 0},
#endif
};
