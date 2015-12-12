if (*dp->d_name == '.' || (
#ifdef _DIRENT_HAVE_D_TYPE
		    dp->d_type == DT_DIR &&
#endif
		    strcmp(dp->d_name, "shm") == 0))
			/* ignore /dev/.{udev,mount,mdadm} and /dev/shm */
			continue;
