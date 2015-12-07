#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,0)
if (sk->dead)
#else
	if (sock_flag(sk, SOCK_DEAD))
#endif
	{
	    release_sock(sk);
	    return -EBADF;
	}
