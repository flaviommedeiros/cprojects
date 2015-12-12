static const struct blkid_idinfo *idinfos[] =
{
#ifdef __linux__
	&ioctl_tp_idinfo,
	&sysfs_tp_idinfo,
	&md_tp_idinfo,
	&dm_tp_idinfo,
	&lvm_tp_idinfo,
	&evms_tp_idinfo
#endif
};
