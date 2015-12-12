switch (result) {
#ifdef CONFIG_NET_CLS_ACT
		case TC_ACT_QUEUED:
		case TC_ACT_STOLEN:
			kfree_skb(skb);
			return NET_XMIT_SUCCESS | __NET_XMIT_STOLEN;

		case TC_ACT_SHOT:
			goto drop;
#endif
		case TC_ACT_OK:
			skb->tc_index = TC_H_MIN(res.classid);
			break;

		default:
			if (p->default_index != NO_DEFAULT_INDEX)
				skb->tc_index = p->default_index;
			break;
		}
