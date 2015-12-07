#ifdef CONFIG_TR
if (priv->is_trdev)
				src =
				    ((struct lecdatahdr_8025 *)skb->data)->
				    h_source;
			else
#endif
				src =
				    ((struct lecdatahdr_8023 *)skb->data)->
				    h_source;
