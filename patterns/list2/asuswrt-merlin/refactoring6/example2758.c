if (CTF_ENAB(et->cih) &&
#ifdef CONFIG_IP_NF_DNSMQ
		!dnsmq_hit &&
#endif
		(ret = ctf_forward(et->cih, skb, skb->dev)) != BCME_ERROR) {
		if (ret == BCME_EPERM) {
			PKTFRMNATIVE(et->osh, skb);
			PKTFREE(et->osh, skb, FALSE);
		}
		return (BCME_OK);
	}
