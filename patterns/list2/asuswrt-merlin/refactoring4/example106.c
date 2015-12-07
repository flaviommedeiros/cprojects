#ifndef LINUX_2_6_36
if (!iptc_flush_entries(chain, &handle) ||
	    !iptc_commit(&handle))
#else
	if (!iptc_flush_entries(chain, handle) ||
	    !iptc_commit(handle))
#endif /* linux-2.6.36 */
		goto err;
