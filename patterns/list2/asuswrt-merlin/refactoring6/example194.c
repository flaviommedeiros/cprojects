if (!(handle = iptc_init("filter")) ||
#ifndef LINUX_2_6_36
	    !iptc_insert_entry("FORWARD", entry, 0, &handle) ||
	    !iptc_commit(&handle)) {
#else
	    !iptc_insert_entry("FORWARD", entry, 0, handle) ||
	    !iptc_commit(handle)) {
#endif /* linux-2.6.36 */
#ifdef LINUX_2_6_36
		if (handle)
			iptc_free(handle);
#endif
		fprintf(stderr, "%s\n", iptc_strerror(errno));
		free(entry);
		return errno;
	}
