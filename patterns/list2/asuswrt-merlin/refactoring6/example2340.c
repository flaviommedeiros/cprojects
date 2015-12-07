if ((dev->flags&IFF_LOOPBACK) ||
	    dev->type == ARPHRD_TUNNEL ||
#if defined(CONFIG_IPV6_SIT) || defined(CONFIG_IPV6_SIT_MODULE)
	    dev->type == ARPHRD_SIT ||
#endif
	    dev->type == ARPHRD_NONE) {
		printk(KERN_INFO
		       "%s: Disabled Privacy Extensions\n",
		       dev->name);
		ndev->cnf.use_tempaddr = -1;
	} else {
		in6_dev_hold(ndev);
		ipv6_regen_rndid((unsigned long) ndev);
	}
