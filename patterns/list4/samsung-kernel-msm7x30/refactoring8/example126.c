static struct usb_descriptor_header *gser_fs_function[] = {
	(struct usb_descriptor_header *) &gser_interface_desc,
#ifdef CONFIG_MODEM_SUPPORT
	(struct usb_descriptor_header *) &gser_header_desc,
	(struct usb_descriptor_header *) &gser_call_mgmt_descriptor,
	(struct usb_descriptor_header *) &gser_descriptor,
	(struct usb_descriptor_header *) &gser_union_desc,
	(struct usb_descriptor_header *) &gser_fs_notify_desc,
#endif
	(struct usb_descriptor_header *) &gser_fs_in_desc,
	(struct usb_descriptor_header *) &gser_fs_out_desc,
	NULL,
};
