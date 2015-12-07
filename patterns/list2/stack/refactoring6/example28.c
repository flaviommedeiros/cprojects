if (sk_mc_loop(sk)
#ifdef CONFIG_IP_MROUTE
		/* Small optimization: do not loopback not local frames,
		   which returned after forwarding; they will be  dropped
		   by ip_mr_input in any case.
		   Note, that local frames are looped back to be delivered
		   to local recipients.

		   This check is duplicated in ip_mr_input at the moment.
		 */
		    &&
		    ((rt->rt_flags & RTCF_LOCAL) ||
		     !(IPCB(skb)->flags & IPSKB_FORWARDED))
#endif
		   ) {
			struct sk_buff *newskb = skb_clone(skb, GFP_ATOMIC);
			if (newskb)
				NF_HOOK(NFPROTO_IPV4, NF_INET_POST_ROUTING,
					sk, newskb, NULL, newskb->dev,
					dev_loopback_xmit);
		}
