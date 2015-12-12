static int set_expected_rtp_rtcp(struct sk_buff *skb, unsigned int dataoff,
				 const char **dptr, unsigned int *datalen,
				 union nf_inet_addr *daddr, __be16 port,
				 enum sip_expectation_classes class,
				 unsigned int mediaoff, unsigned int medialen)
{
	struct nf_conntrack_expect *exp, *rtp_exp, *rtcp_exp;
	enum ip_conntrack_info ctinfo;
	struct nf_conn *ct = nf_ct_get(skb, &ctinfo);
	struct net *net = nf_ct_net(ct);
	enum ip_conntrack_dir dir = CTINFO2DIR(ctinfo);
	union nf_inet_addr *saddr;
	struct nf_conntrack_tuple tuple;
	int direct_rtp = 0, skip_expect = 0, ret = NF_DROP;
	u_int16_t base_port;
	__be16 rtp_port, rtcp_port;
	typeof(nf_nat_sdp_port_hook) nf_nat_sdp_port;
	typeof(nf_nat_sdp_media_hook) nf_nat_sdp_media;

	saddr = NULL;
	if (sip_direct_media) {
		if (!nf_inet_addr_cmp(daddr, &ct->tuplehash[dir].tuple.src.u3))
			return NF_ACCEPT;
		saddr = &ct->tuplehash[!dir].tuple.src.u3;
	}

	/* We need to check whether the registration exists before attempting
	 * to register it since we can see the same media description multiple
	 * times on different connections in case multiple endpoints receive
	 * the same call.
	 *
	 * RTP optimization: if we find a matching media channel expectation
	 * and both the expectation and this connection are SNATed, we assume
	 * both sides can reach each other directly and use the final
	 * destination address from the expectation. We still need to keep
	 * the NATed expectations for media that might arrive from the
	 * outside, and additionally need to expect the direct RTP stream
	 * in case it passes through us even without NAT.
	 */
	memset(&tuple, 0, sizeof(tuple));
	if (saddr)
		tuple.src.u3 = *saddr;
	tuple.src.l3num		= nf_ct_l3num(ct);
	tuple.dst.protonum	= IPPROTO_UDP;
	tuple.dst.u3		= *daddr;
	tuple.dst.u.udp.port	= port;

	rcu_read_lock();
	do {
		exp = __nf_ct_expect_find(net, nf_ct_zone(ct), &tuple);

		if (!exp || exp->master == ct ||
		    nfct_help(exp->master)->helper != nfct_help(ct)->helper ||
		    exp->class != class)
			break;
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
	} while (!skip_expect);
	rcu_read_unlock();

	base_port = ntohs(tuple.dst.u.udp.port) & ~1;
	rtp_port = htons(base_port);
	rtcp_port = htons(base_port + 1);

	if (direct_rtp) {
		nf_nat_sdp_port = rcu_dereference(nf_nat_sdp_port_hook);
		if (nf_nat_sdp_port &&
		    !nf_nat_sdp_port(skb, dataoff, dptr, datalen,
				     mediaoff, medialen, ntohs(rtp_port)))
			goto err1;
	}

	if (skip_expect)
		return NF_ACCEPT;

	rtp_exp = nf_ct_expect_alloc(ct);
	if (rtp_exp == NULL)
		goto err1;
	nf_ct_expect_init(rtp_exp, class, nf_ct_l3num(ct), saddr, daddr,
			  IPPROTO_UDP, NULL, &rtp_port);

	rtcp_exp = nf_ct_expect_alloc(ct);
	if (rtcp_exp == NULL)
		goto err2;
	nf_ct_expect_init(rtcp_exp, class, nf_ct_l3num(ct), saddr, daddr,
			  IPPROTO_UDP, NULL, &rtcp_port);

	nf_nat_sdp_media = rcu_dereference(nf_nat_sdp_media_hook);
	if (nf_nat_sdp_media && ct->status & IPS_NAT_MASK && !direct_rtp)
		ret = nf_nat_sdp_media(skb, dataoff, dptr, datalen,
				       rtp_exp, rtcp_exp,
				       mediaoff, medialen, daddr);
	else {
		if (nf_ct_expect_related(rtp_exp) == 0) {
			if (nf_ct_expect_related(rtcp_exp) != 0)
				nf_ct_unexpect_related(rtp_exp);
			else
				ret = NF_ACCEPT;
		}
	}
	nf_ct_expect_put(rtcp_exp);
err2:
	nf_ct_expect_put(rtp_exp);
err1:
	return ret;
}
