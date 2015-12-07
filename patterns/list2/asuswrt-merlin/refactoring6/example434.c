if (err == -ENOPROTOOPT && optname != IP_PKTOPTIONS
#ifdef CONFIG_IP_MROUTE
	    && (optname < MRT_BASE || optname > MRT_BASE+10)
#endif
	   ) {
		int len;

		if (get_user(len, optlen))
			return -EFAULT;

		lock_sock(sk);
		err = compat_nf_getsockopt(sk, PF_INET, optname, optval, &len);
		release_sock(sk);
		if (err >= 0)
			err = put_user(len, optlen);
		return err;
	}
