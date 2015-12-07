#ifdef CONFIG_NET
if (S_ISSOCK(filp->f_path.dentry->d_inode->i_mode) &&
	    cmd >= SIOCDEVPRIVATE && cmd <= (SIOCDEVPRIVATE + 15)) {
		error = siocdevprivate_ioctl(fd, cmd, arg);
	} else
#endif
	{
		static int count;

		if (++count <= 50)
			compat_ioctl_error(filp, fd, cmd, arg);
		error = -EINVAL;
	}
