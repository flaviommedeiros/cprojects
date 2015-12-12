switch (i) {
	case IPV6_SADDR_RULE_INIT:
		/* Rule 0: remember if hiscore is not ready yet */
		ret = !!score->ifa;
		break;
	case IPV6_SADDR_RULE_LOCAL:
		/* Rule 1: Prefer same address */
		ret = ipv6_addr_equal(&score->ifa->addr, dst->addr);
		break;
	case IPV6_SADDR_RULE_SCOPE:
		/* Rule 2: Prefer appropriate scope
		 *
		 *      ret
		 *       ^
		 *    -1 |  d 15
		 *    ---+--+-+---> scope
		 *       |
		 *       |             d is scope of the destination.
		 *  B-d  |  \
		 *       |   \      <- smaller scope is better if
		 *  B-15 |    \        if scope is enough for destinaion.
		 *       |             ret = B - scope (-1 <= scope >= d <= 15).
		 * d-C-1 | /
		 *       |/         <- greater is better
		 *   -C  /             if scope is not enough for destination.
		 *      /|             ret = scope - C (-1 <= d < scope <= 15).
		 *
		 * d - C - 1 < B -15 (for all -1 <= d <= 15).
		 * C > d + 14 - B >= 15 + 14 - B = 29 - B.
		 * Assume B = 0 and we get C > 29.
		 */
		ret = __ipv6_addr_src_scope(score->addr_type);
		if (ret >= dst->scope)
			ret = -ret;
		else
			ret -= 128;	/* 30 is enough */
		score->scopedist = ret;
		break;
	case IPV6_SADDR_RULE_PREFERRED:
		/* Rule 3: Avoid deprecated and optimistic addresses */
		ret = ipv6_saddr_preferred(score->addr_type) ||
		      !(score->ifa->flags & (IFA_F_DEPRECATED|IFA_F_OPTIMISTIC));
		break;
#ifdef CONFIG_IPV6_MIP6
	case IPV6_SADDR_RULE_HOA:
	    {
		/* Rule 4: Prefer home address */
		int prefhome = !(dst->prefs & IPV6_PREFER_SRC_COA);
		ret = !(score->ifa->flags & IFA_F_HOMEADDRESS) ^ prefhome;
		break;
	    }
#endif
	case IPV6_SADDR_RULE_OIF:
		/* Rule 5: Prefer outgoing interface */
		ret = (!dst->ifindex ||
		       dst->ifindex == score->ifa->idev->dev->ifindex);
		break;
	case IPV6_SADDR_RULE_LABEL:
		/* Rule 6: Prefer matching label */
		ret = ipv6_addr_label(net,
				      &score->ifa->addr, score->addr_type,
				      score->ifa->idev->dev->ifindex) == dst->label;
		break;
#ifdef CONFIG_IPV6_PRIVACY
	case IPV6_SADDR_RULE_PRIVACY:
	    {
		/* Rule 7: Prefer public address
		 * Note: prefer temporary address if use_tempaddr >= 2
		 */
		int preftmp = dst->prefs & (IPV6_PREFER_SRC_PUBLIC|IPV6_PREFER_SRC_TMP) ?
				!!(dst->prefs & IPV6_PREFER_SRC_TMP) :
				score->ifa->idev->cnf.use_tempaddr >= 2;
		ret = (!(score->ifa->flags & IFA_F_TEMPORARY)) ^ preftmp;
		break;
	    }
#endif
	case IPV6_SADDR_RULE_ORCHID:
		/* Rule 8-: Prefer ORCHID vs ORCHID or
		 *	    non-ORCHID vs non-ORCHID
		 */
		ret = !(ipv6_addr_orchid(&score->ifa->addr) ^
			ipv6_addr_orchid(dst->addr));
		break;
	case IPV6_SADDR_RULE_PREFIX:
		/* Rule 8: Use longest matching prefix */
		ret = ipv6_addr_diff(&score->ifa->addr, dst->addr);
		if (ret > score->ifa->prefix_len)
			ret = score->ifa->prefix_len;
		score->matchlen = ret;
		break;
	default:
		ret = 0;
	}
