if (!(handle = iptc_init(ipt_table_name[fw->target])) ||
#ifndef LINUX_2_6_36
	    !iptc_delete_num_entry(chain, num, &handle) ||
	    !iptc_commit(&handle)) {
#else
	    !iptc_delete_num_entry(chain, num, handle) ||
	    !iptc_commit(handle)) {
#endif /* linux-2.6.36 */
#ifdef LINUX_2_6_36
		if (handle)
			iptc_free(handle);
#endif
		fprintf(stderr, "%s\n", iptc_strerror(errno));
		return errno;
	}
