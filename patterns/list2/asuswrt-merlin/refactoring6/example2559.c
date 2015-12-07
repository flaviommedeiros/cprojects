if (!(handle = iptc_init("filter")) ||
#ifndef LINUX_2_6_36
	    !iptc_insert_entry("logaccept", entry, 0, &handle) ||
	    !iptc_commit(&handle))
#else
	    !iptc_insert_entry("logaccept", entry, 0, handle) ||
	    !iptc_commit(handle)
