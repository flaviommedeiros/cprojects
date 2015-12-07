#ifdef CONFIG_NET_POLL_CONTROLLER
if (unlikely(bond->dev->priv_flags & IFF_IN_NETPOLL)) {
		struct netpoll *np = bond->dev->npinfo->netpoll;
		slave_dev->npinfo = bond->dev->npinfo;
		np->real_dev = np->dev = skb->dev;
		slave_dev->priv_flags |= IFF_IN_NETPOLL;
		netpoll_send_skb(np, skb);
		slave_dev->priv_flags &= ~IFF_IN_NETPOLL;
		np->dev = bond->dev;
	} else
#endif
		dev_queue_xmit(skb);
