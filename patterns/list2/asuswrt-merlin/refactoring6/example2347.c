if (err == -ENOPROTOOPT && optname != IP_HDRINCL &&
		optname != IP_IPSEC_POLICY && optname != IP_XFRM_POLICY
#ifdef CONFIG_IP_MROUTE
		&& (optname < MRT_BASE || optname > (MRT_BASE + 10))
#endif
	   ) {
		lock_sock(sk);
		err = nf_setsockopt(sk, PF_INET, optname, optval, optlen);
		release_sock(sk);
	}
