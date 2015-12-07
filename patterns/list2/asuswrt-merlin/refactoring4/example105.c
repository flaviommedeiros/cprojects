#ifndef LINUX_2_6_36
if (!iptc_create_chain(chain, &handle))
#else
		if (!iptc_create_chain(chain, handle))
#endif /* linux-2.6.36 */
			goto err;
