static struct device_attribute *const fw_ne_attrs[] = {
	&dev_attr_ne_guid,
	&dev_attr_ne_guid_vendor_id,
	&dev_attr_ne_capabilities,
	&dev_attr_ne_vendor_id,
	&dev_attr_ne_nodeid,
	&dev_attr_bus_options,
#ifdef HPSB_DEBUG_TLABELS
	&dev_attr_tlabels_free,
	&dev_attr_tlabels_mask,
#endif
};
