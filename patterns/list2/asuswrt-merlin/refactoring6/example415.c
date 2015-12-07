if (
#ifdef CONFIG_NET_CLS_POLICE
	    result == TC_POLICE_SHOT ||
#endif
	    (ret = flow->q->enqueue(skb,flow->q)) != 0) {
		sch->qstats.drops++;
		if (flow) flow->qstats.drops++;
		return ret;
	}
