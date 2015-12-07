#ifdef BCM_VLAN
if ((bp->vlgrp != NULL) && vlan_tx_tag_present(skb) &&
	    (bp->flags & HW_VLAN_TX_FLAG)) {
		tx_start_bd->vlan = cpu_to_le16(vlan_tx_tag_get(skb));
		tx_start_bd->bd_flags.as_bitfield |= ETH_TX_BD_FLAGS_VLAN_TAG;
	} else
#endif
		tx_start_bd->vlan = cpu_to_le16(pkt_prod);
