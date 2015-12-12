#ifdef CONFIG_TR
if (priv->is_trdev)
			dst = ((struct lecdatahdr_8025 *)skb->data)->h_dest;
		else
#endif
			dst = ((struct lecdatahdr_8023 *)skb->data)->h_dest;
