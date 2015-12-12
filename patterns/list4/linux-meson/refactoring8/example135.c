static struct vio_device_id hvc_driver_table[] = {
	{"serial", "hvterm1"},
#ifndef HVC_OLD_HVSI
	{"serial", "hvterm-protocol"},
#endif
	{ "", "" }
};
