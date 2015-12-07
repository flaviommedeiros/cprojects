if ((l2tp->conn_id == tunnel_id) &&
#ifdef CONFIG_NET_NS
		    (sk->sk_net == net) &&
#endif
		    !(inet->inet_rcv_saddr && inet->inet_rcv_saddr != laddr) &&
		    !(sk->sk_bound_dev_if && sk->sk_bound_dev_if != dif))
			goto found;
