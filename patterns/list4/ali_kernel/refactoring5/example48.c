#ifdef CONFIG_NET_POLL_CONTROLLER
if (unlikely(bond->dev->priv_flags & IFF_IN_NETPOLL)) {
		struct netpoll *np = bond->dev->npinfo->netpoll;
		slave_dev->npinfo = bond->dev->npinfo;
		slave_dev->priv_flags |= IFF_IN_NETPOLL;
		netpoll_send_skb_on_dev(np, skb, slave_dev);
		slave_dev->priv_flags &= ~IFF_IN_NETPOLL;
	} else
#endif
		dev_queue_xmit(skb);
