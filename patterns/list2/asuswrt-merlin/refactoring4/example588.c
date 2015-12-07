#ifdef CONFIG_BCM47XX
if (copied && !(flags & MSG_MORE))
#else
	if (copied)
#endif
		tcp_push(sk, flags, mss_now, tp->nonagle);
