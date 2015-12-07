if (gnet_stats_copy_basic(&d, &h->tcf_bstats) < 0 ||
#ifdef CONFIG_NET_ESTIMATOR
	    gnet_stats_copy_rate_est(&d, &h->tcf_rate_est) < 0 ||
#endif
	    gnet_stats_copy_queue(&d, &h->tcf_qstats) < 0)
		goto errout;
