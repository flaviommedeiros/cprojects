#ifdef CONFIG_NCPFS_EXTRAS
if (NCP_SERVER(dir)->m.flags & NCP_MOUNT_SYMLINKS)
		kludge = 1;
	else
#endif
	/* EPERM is returned by VFS if symlink procedure does not exist */
		return -EPERM;
