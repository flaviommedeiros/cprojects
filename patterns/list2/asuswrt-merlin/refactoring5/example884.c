#ifdef BCM_VLAN
if ((status & L2_FHDR_STATUS_L2_VLAN_TAG) && (bp->vlgrp != 0)) {
			vlan_hwaccel_receive_skb(skb, bp->vlgrp,
				rx_hdr->l2_fhdr_vlan_tag);
		}
		else
#endif
			netif_receive_skb(skb);
