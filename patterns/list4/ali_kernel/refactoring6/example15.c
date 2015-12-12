if ((old_vid != (u16)IGB_MNG_VLAN_NONE) &&
	    (vid != old_vid) &&
#ifdef HAVE_VLAN_RX_REGISTER
	    !vlan_group_get_device(adapter->vlgrp, old_vid)) {
#else
	    !test_bit(old_vid, adapter->active_vlans)) {
#endif
		/* remove VID from filter table */
		igb_vfta_set(adapter, old_vid, FALSE);
	}
