const struct nvif_driver *
nvif_drivers[] = {
#ifdef __KERNEL__
	&nvif_driver_nvkm,
#else
	&nvif_driver_drm,
	&nvif_driver_lib,
#endif
	NULL
};
