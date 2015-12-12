#ifdef HAVE_IPV6
if (srv->ipv6) {
		cherokee_buffer_add_str (&n, ", IPv6 enabled");
	} else
#endif
		cherokee_buffer_add_str (&n, ", IPv6 disabled");
