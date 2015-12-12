#ifdef NS_USE_DESTRUCTORS
if (card->lbfqc < card->lbnr.min)
#else
	if (card->lbfqc < card->lbnr.init) {
		struct sk_buff *new_lb;
		if ((new_lb = dev_alloc_skb(NS_LGSKBSIZE)) != NULL) {
			NS_PRV_BUFTYPE(new_lb) = BUF_LG;
			skb_queue_tail(&card->lbpool.queue, new_lb);
			skb_reserve(new_lb, NS_SMBUFSIZE);
			push_rxbufs(card, new_lb);
		}
	}
