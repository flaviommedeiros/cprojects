if ((session->ifname[0] &&
	     nla_put_string(skb, L2TP_ATTR_IFNAME, session->ifname)) ||
	    (session->cookie_len &&
	     nla_put(skb, L2TP_ATTR_COOKIE, session->cookie_len,
		     &session->cookie[0])) ||
	    (session->peer_cookie_len &&
	     nla_put(skb, L2TP_ATTR_PEER_COOKIE, session->peer_cookie_len,
		     &session->peer_cookie[0])) ||
	    nla_put_u8(skb, L2TP_ATTR_RECV_SEQ, session->recv_seq) ||
	    nla_put_u8(skb, L2TP_ATTR_SEND_SEQ, session->send_seq) ||
	    nla_put_u8(skb, L2TP_ATTR_LNS_MODE, session->lns_mode) ||
#ifdef CONFIG_XFRM
	    (((sk) && (sk->sk_policy[0] || sk->sk_policy[1])) &&
	     nla_put_u8(skb, L2TP_ATTR_USING_IPSEC, 1)) ||
#endif
	    (session->reorder_timeout &&
	     nla_put_msecs(skb, L2TP_ATTR_RECV_TIMEOUT, session->reorder_timeout)))
		goto nla_put_failure;
