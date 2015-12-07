if (gnet_stats_copy_basic(d, &cl->bstats) < 0 ||
#ifdef CONFIG_NET_ESTIMATOR
	    gnet_stats_copy_rate_est(d, &cl->rate_est) < 0 ||
#endif
	    gnet_stats_copy_queue(d, &cl->qstats) < 0)
		return -1;
