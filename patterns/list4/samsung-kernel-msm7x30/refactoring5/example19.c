#ifdef CONFIG_TR
if (card->dev->type == ARPHRD_IEEE802_TR)
		skb->protocol = tr_type_trans(skb, card->dev);
	else
#endif
		skb->protocol = eth_type_trans(skb, card->dev);
