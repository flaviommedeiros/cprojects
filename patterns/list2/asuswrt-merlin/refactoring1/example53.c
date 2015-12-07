if (ct->tuplehash[dir].tuple.dst.u3.ip !=
		    ct->tuplehash[!dir].tuple.src.u3.ip) {
			if (ip_route_me_harder(pskb, RTN_UNSPEC))
				ret = NF_DROP;
		}
#ifdef CONFIG_XFRM
		else if (ct->tuplehash[dir].tuple.dst.u.all !=
			 ct->tuplehash[!dir].tuple.src.u.all)
			if (ip_xfrm_me_harder(pskb))
				ret = NF_DROP;
#endif
