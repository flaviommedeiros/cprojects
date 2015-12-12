#ifdef CONFIG_NF_NAT_NEEDED
if (!direct_rtp &&
		    (!nf_inet_addr_cmp(&exp->saved_addr, &exp->tuple.dst.u3) ||
		     exp->saved_proto.udp.port != exp->tuple.dst.u.udp.port) &&
		    ct->status & IPS_NAT_MASK) {
			*daddr			= exp->saved_addr;
			tuple.dst.u3		= exp->saved_addr;
			tuple.dst.u.udp.port	= exp->saved_proto.udp.port;
			direct_rtp = 1;
		} else
#endif
			skip_expect = 1;
