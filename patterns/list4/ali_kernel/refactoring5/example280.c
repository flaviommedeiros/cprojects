#ifdef CONFIG_NET_POLL_CONTROLLER
if (unlikely(netpoll_tx_running(skb->dev))) {
				if (skb->dev->npinfo)
					netpoll_send_skb(skb->dev->npinfo->netpoll, skb);
				skb->dev->priv_flags &= ~IFF_IN_NETPOLL;
			} else
#endif
				dev_queue_xmit(skb);
