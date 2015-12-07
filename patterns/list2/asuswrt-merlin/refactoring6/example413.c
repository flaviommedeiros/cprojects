if (gnet_stats_copy_basic(&d, &police->tcf_bstats) < 0 ||
#ifdef CONFIG_NET_ESTIMATOR
	    gnet_stats_copy_rate_est(&d, &police->tcf_rate_est) < 0 ||
#endif
	    gnet_stats_copy_queue(&d, &police->tcf_qstats) < 0)
		goto errout;
