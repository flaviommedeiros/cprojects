#ifdef CONFIG_MODULES
if (!ss)
#endif
		{
			nfnl_unlock(subsys_id);
			netlink_ack(skb, nlh, -EOPNOTSUPP);
			return kfree_skb(skb);
		}
