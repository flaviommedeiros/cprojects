if ((vlvf & VLAN_VID_MASK) == vid &&
#ifndef HAVE_VLAN_RX_REGISTER
		    !test_bit(vid, adapter->active_vlans) &&
#endif
		    !bits)
			igb_vlvf_set(adapter, vid, add,
				     adapter->vfs_allocated_count);
