if ((rt == NULL) || (
#ifdef CONFIG_IPV6
			!IPVERSION_IS_4(ipver) ?
			 ((rt->dst.input != ip6_forward) ||
			  !(ipv6_addr_type(&ip6h->daddr) & IPV6_ADDR_UNICAST)) :
#endif /* CONFIG_IPV6 */
			 ((rt->dst.input != ip_forward) || (rt->rt_type != RTN_UNICAST))) ||
			(rt->dst.neighbour == NULL) ||
			((rt->dst.neighbour->nud_state & nud_flags) == 0))
		return;
