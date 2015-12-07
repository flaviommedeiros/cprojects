if (gnet_stats_copy_basic(&d, &q->bstats) < 0 ||
#ifdef CONFIG_NET_ESTIMATOR
	    gnet_stats_copy_rate_est(&d, &q->rate_est) < 0 ||
#endif
	    gnet_stats_copy_queue(&d, &q->qstats) < 0)
		goto rtattr_failure;
