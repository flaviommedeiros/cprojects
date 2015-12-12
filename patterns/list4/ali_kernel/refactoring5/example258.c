#ifdef CONFIG_TR
if (priv->is_trdev)
			skb->protocol = tr_type_trans(skb, dev);
		else
#endif
			skb->protocol = eth_type_trans(skb, dev);
