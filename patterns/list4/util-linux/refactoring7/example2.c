return
		d &&
#ifdef _DIRENT_HAVE_D_TYPE
		(d->d_type == DT_DIR || d->d_type == DT_UNKNOWN) &&
#endif
		strncmp(d->d_name, "node", 4) == 0 &&
		isdigit_string(d->d_name + 4);
