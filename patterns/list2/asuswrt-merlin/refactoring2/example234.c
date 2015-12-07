#if defined(RTCONFIG_RALINK_MT7620)
if ((r = mt7620_vlan_set(-1, v, portmap, v)) != 0)
#elif defined(RTCONFIG_RALINK_MT7621)
			if ((r = mt7621_vlan_set(-1, v, portmap, v)) != 0)
#endif			   
				isp_profile_hwnat_not_safe = 1;
