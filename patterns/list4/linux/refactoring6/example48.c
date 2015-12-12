if (ip6_rt_check(&rt->rt6i_dst, &fl6->daddr, np->daddr_cache) ||
#ifdef CONFIG_IPV6_SUBTREES
	    ip6_rt_check(&rt->rt6i_src, &fl6->saddr, np->saddr_cache) ||
#endif
	   (!(fl6->flowi6_flags & FLOWI_FLAG_SKIP_NH_OIF) &&
	      (fl6->flowi6_oif && fl6->flowi6_oif != dst->dev->ifindex))) {
		dst_release(dst);
		dst = NULL;
	}
