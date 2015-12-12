static struct configfs_attribute *fsg_attrs[] = {
	&fsg_opts_attr_stall,
#ifdef CONFIG_USB_GADGET_DEBUG_FILES
	&fsg_opts_attr_num_buffers,
#endif
	NULL,
};
