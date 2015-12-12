#ifdef CONFIG_NET_DMA
if (copied_early)
				__skb_queue_tail(&sk->sk_async_wait_queue, skb);
			else
#endif
			if (eaten)
				kfree_skb_partial(skb, fragstolen);
