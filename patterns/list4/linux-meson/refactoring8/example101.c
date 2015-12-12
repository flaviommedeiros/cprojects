static struct class_attribute efuse_class_attrs[] = {

	__ATTR_RO(mac),

	__ATTR_RO(mac_wifi),

	__ATTR_RO(mac_bt),

	#ifndef EFUSE_READ_ONLY		/*make the efuse can not be write through sysfs */
	__ATTR(userdata, S_IRWXU, userdata_show, userdata_write),

	#else
	__ATTR_RO(userdata),

	#endif
	__ATTR_NULL

};
