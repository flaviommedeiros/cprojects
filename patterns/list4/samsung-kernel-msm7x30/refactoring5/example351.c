#ifdef CONFIG_NF_NAT_NEEDED
if (exp->tuple.src.l3num == AF_INET && !direct_rtp &&
		    (exp->saved_ip != exp->tuple.dst.u3.ip ||
		     exp->saved_proto.udp.port != exp->tuple.dst.u.udp.port) &&
		    ct->status & IPS_NAT_MASK) {
			daddr->ip		= exp->saved_ip;
			tuple.dst.u3.ip		= exp->saved_ip;
			tuple.dst.u.udp.port	= exp->saved_proto.udp.port;
			direct_rtp = 1;
		} else
#endif
			skip_expect = 1;
