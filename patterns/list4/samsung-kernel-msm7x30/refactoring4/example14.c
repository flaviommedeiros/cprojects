#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 36))
if ((p = pskb_copy((struct sk_buff *)skb, flags)) == NULL)
#else
	if ((p = skb_clone((struct sk_buff *)skb, GFP_ATOMIC)) == NULL)
#endif
		return NULL;
