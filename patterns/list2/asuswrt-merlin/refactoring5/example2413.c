#ifdef MSNFS
if ((fhp->fh_export->ex_flags & NFSEXP_MSNFS) &&
			(atomic_read(&rdentry->d_count) > 1)) {
			host_err = -EPERM;
		} else
#endif
		host_err = vfs_unlink(dirp, rdentry);
