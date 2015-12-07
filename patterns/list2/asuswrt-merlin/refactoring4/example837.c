#ifdef NS_USE_DESTRUCTORS
if (card->sbfqc < card->sbnr.min)
#else
	if (card->sbfqc < card->sbnr.init) {
		struct sk_buff *new_sb;
		if ((new_sb = dev_alloc_skb(NS_SMSKBSIZE)) != NULL) {
			NS_PRV_BUFTYPE(new_sb) = BUF_SM;
			skb_queue_tail(&card->sbpool.queue, new_sb);
			skb_reserve(new_sb, NS_AAL0_HEADER);
			push_rxbufs(card, new_sb);
		}
	}
