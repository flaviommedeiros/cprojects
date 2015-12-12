static unsigned int features[] = {
	VIRTIO_SCSI_F_HOTPLUG,
	VIRTIO_SCSI_F_CHANGE,
#ifdef CONFIG_BLK_DEV_INTEGRITY
	VIRTIO_SCSI_F_T10_PI,
#endif
};
