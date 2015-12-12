static struct virtio_device_id rproc_serial_id_table[] = {
#if IS_ENABLED(CONFIG_REMOTEPROC)
	{ VIRTIO_ID_RPROC_SERIAL, VIRTIO_DEV_ANY_ID },
#endif
	{ 0 },
};
