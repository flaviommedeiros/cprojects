#ifdef NETIF_F_HW_VLAN_CTAG_RX
if (changed & NETIF_F_HW_VLAN_CTAG_RX)
#else
	if (changed & NETIF_F_HW_VLAN_RX)
#endif
		igb_vlan_mode(netdev, features);
