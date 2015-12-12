#ifdef CONFIG_SYN_COOKIES
if (unlikely(req->cookie_ts))
		skb->skb_mstamp.stamp_jiffies = cookie_init_timestamp(req);
	else
#endif
	skb_mstamp_get(&skb->skb_mstamp);
