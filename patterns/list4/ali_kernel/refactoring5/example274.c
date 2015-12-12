#ifdef CONFIG_SYN_COOKIES
if (sysctl_tcp_syncookies)
		printk(KERN_INFO
		       "TCPv6: Possible SYN flooding on port %d. "
		       "Sending cookies.\n", ntohs(tcp_hdr(skb)->dest));
	else
#endif
		printk(KERN_INFO
		       "TCPv6: Possible SYN flooding on port %d. "
		       "Dropping request.\n", ntohs(tcp_hdr(skb)->dest));
