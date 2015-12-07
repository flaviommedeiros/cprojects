#ifdef VLAN_SUPPORT
if (np->vlgrp && le16_to_cpu(desc->status2) & 0x0200) {
			u16 vlid = le16_to_cpu(desc->vlanid);

			if (debug > 4) {
				printk(KERN_DEBUG "  netdev_rx() vlanid = %d\n",
				       vlid);
			}
			/*
			 * vlan_hwaccel_rx expects a packet with the VLAN tag
			 * stripped out.
			 */
			vlan_hwaccel_rx(skb, np->vlgrp, vlid);
		} else
#endif /* VLAN_SUPPORT */
			netif_receive_skb(skb);
