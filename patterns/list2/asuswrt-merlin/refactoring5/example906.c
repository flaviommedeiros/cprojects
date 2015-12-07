#ifdef CONFIG_QETH_VLAN
if (vlan_tag)
			if (card->vlangrp)
				vlan_hwaccel_rx(skb, card->vlangrp, vlan_tag);
			else {
				dev_kfree_skb_any(skb);
				continue;
			}
		else
#endif
			rxrc = netif_rx(skb);
