#if defined(__FreeBSD__)
if (mount("cgroup", cgns->mnt_point,
		  MS_NOSUID|MS_NOEXEC|MS_NODEV, options))
#else
	if (mount("cgroup", cgns->mnt_point, "cgroup",
		  MS_NOSUID|MS_NOEXEC|MS_NODEV, options))
#endif
		return XCGROUP_ERROR;
	else {
		/* FIXME: this only gets set when we aren't mounted at
		   all.  Since we never umount this may only be loaded
		   at startup the first time.
		*/

		/* we then set the release_agent if necessary */
		if (cgns->notify_prog) {
			if (xcgroup_create(cgns, &cg, "/", 0, 0) ==
			     XCGROUP_ERROR)
				return XCGROUP_SUCCESS;
			xcgroup_set_param(&cg, "release_agent",
					  cgns->notify_prog);
			xcgroup_destroy(&cg);
		}
		return XCGROUP_SUCCESS;
	}
