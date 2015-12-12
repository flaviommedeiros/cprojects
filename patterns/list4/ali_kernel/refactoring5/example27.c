#ifdef IFLA_VF_MAX
if (vf_data->pf_vlan)
			DPRINTK(DRV, INFO,
				"VF %d attempted to override administratively "
				"set VLAN tag\nReload the VF driver to "
				"resume operations\n", vf);
		else
#endif
			retval = igb_set_vf_vlan(adapter, msgbuf, vf);
