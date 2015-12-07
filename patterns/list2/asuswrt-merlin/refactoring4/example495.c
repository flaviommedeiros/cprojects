#ifdef DMA
if (!PKTISCTF(et->osh, skb))
			pktcnt = skb_shinfo(skb)->nr_frags + 1;
		else
			pktcnt = PKTCCNT(skb);
