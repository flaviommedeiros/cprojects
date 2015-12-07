if (ip6_rt_check(&rt->rt6i_dst, &fl->fl6_dst, np->daddr_cache) ||
#ifdef CONFIG_IPV6_SUBTREES
	    ip6_rt_check(&rt->rt6i_src, &fl->fl6_src, np->saddr_cache) ||
#endif
	    (fl->oif && fl->oif != dst->dev->ifindex)) {
		dst_release(dst);
		dst = NULL;
	}
