#ifndef IGB_NO_LRO
if (igb_can_lro(rx_ring, rx_desc, skb))
			igb_lro_receive(q_vector, skb);
		else
#endif
#ifdef HAVE_VLAN_RX_REGISTER
			igb_receive_skb(q_vector, skb);
