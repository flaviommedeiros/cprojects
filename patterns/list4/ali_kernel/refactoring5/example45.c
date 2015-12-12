#ifdef BCM_CNIC
if (cid == BNX2X_ISCSI_ETH_CID)
			vlan_mac_obj = &bp->iscsi_l2_mac_obj;
		else
#endif
			vlan_mac_obj = &bp->fp[cid].mac_obj;
