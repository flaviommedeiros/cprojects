#ifdef VLAN_SUPPORT
if (np->vlgrp && le16_to_cpu(desc->status2) & 0x0200) {
			if (debug > 4)
				printk(KERN_DEBUG "  netdev_rx() vlanid = %d\n", le16_to_cpu(desc->vlanid));
			/* vlan_netdev_receive_skb() expects a packet with the VLAN tag stripped out */
			vlan_netdev_receive_skb(skb, np->vlgrp, le16_to_cpu(desc->vlanid) & VLAN_VID_MASK);
		} else
#endif /* VLAN_SUPPORT */
			netdev_receive_skb(skb);
