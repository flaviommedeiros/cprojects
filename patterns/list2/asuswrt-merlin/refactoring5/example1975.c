#ifdef NETIF_F_HW_VLAN_TX
if (adapter->vlgrp && (rxd->status.vlan)) {
				u16 vlan_tag = (rxd->status.vtag>>4) |
					((rxd->status.vtag&7) << 13) |
					((rxd->status.vtag&8) << 9);
				vlan_hwaccel_rx(skb, adapter->vlgrp, vlan_tag);
			} else
#endif
			netif_rx(skb);
