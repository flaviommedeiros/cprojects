#ifdef CONFIG_CIFS_EXPERIMENTAL
if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_CIFS_ACL) {
		/* get more accurate mode via ACL - so force inode refresh */
		cifsInfo->time = 0;
	} else
#endif /* CONFIG_CIFS_EXPERIMENTAL */
		cifsInfo->time = jiffies;
