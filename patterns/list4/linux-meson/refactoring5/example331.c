#ifdef CONFIG_IP_PIMSM
if (assert == IGMPMSG_WHOLEPKT) {
		/* Ugly, but we have no choice with this interface.
		 * Duplicate old header, fix ihl, length etc.
		 * And all this only to mangle msg->im_msgtype and
		 * to set msg->im_mbz to "mbz" :-)
		 */
		skb_push(skb, sizeof(struct iphdr));
		skb_reset_network_header(skb);
		skb_reset_transport_header(skb);
		msg = (struct igmpmsg *)skb_network_header(skb);
		memcpy(msg, skb_network_header(pkt), sizeof(struct iphdr));
		msg->im_msgtype = IGMPMSG_WHOLEPKT;
		msg->im_mbz = 0;
		msg->im_vif = mrt->mroute_reg_vif_num;
		ip_hdr(skb)->ihl = sizeof(struct iphdr) >> 2;
		ip_hdr(skb)->tot_len = htons(ntohs(ip_hdr(pkt)->tot_len) +
					     sizeof(struct iphdr));
	} else
#endif
	{

	/* Copy the IP header */

	skb->network_header = skb->tail;
	skb_put(skb, ihl);
	skb_copy_to_linear_data(skb, pkt->data, ihl);
	ip_hdr(skb)->protocol = 0;	/* Flag to the kernel this is a route add */
	msg = (struct igmpmsg *)skb_network_header(skb);
	msg->im_vif = vifi;
	skb_dst_set(skb, dst_clone(skb_dst(pkt)));

	/* Add our header */

	igmp = (struct igmphdr *)skb_put(skb, sizeof(struct igmphdr));
	igmp->type	=
	msg->im_msgtype = assert;
	igmp->code	= 0;
	ip_hdr(skb)->tot_len = htons(skb->len);		/* Fix the length */
	skb->transport_header = skb->network_header;
	}
