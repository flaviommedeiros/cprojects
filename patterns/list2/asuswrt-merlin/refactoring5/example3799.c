#ifdef CONFIG_COMPAT
if (compat)
			error = compat_sock_get_timestamp(sk, argp);
		else
#endif
			error = sock_get_timestamp(sk, argp);
