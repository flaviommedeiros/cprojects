#ifdef MSNFS
if ((ffhp->fh_export->ex_flags & NFSEXP_MSNFS) &&
		((atomic_read(&odentry->d_count) > 1)
		 || (atomic_read(&ndentry->d_count) > 1))) {
			host_err = -EPERM;
	} else
#endif
	host_err = vfs_rename(fdir, odentry, tdir, ndentry);
