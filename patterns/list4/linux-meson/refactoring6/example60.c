if (attrib->ether_type == 0x0806
			|| attrib->ether_type == 0x888e
			#ifdef CONFIG_WAPI_SUPPORT
			|| attrib->ether_type == 0x88B4
			#endif
			|| attrib->dhcp_pkt
		) {
			if (0)
				DBG_871X(FUNC_ADPT_FMT" ether_type:0x%04x%s\n", FUNC_ADPT_ARG(xmitframe->padapter)
					, attrib->ether_type, attrib->dhcp_pkt?" DHCP":"");
			allow = _TRUE;
		}
