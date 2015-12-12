#ifdef CONFIG_IOCTL_CFG80211
if(adapter_wdev_data(padapter)->p2p_enabled && pwdinfo->driver_interface == DRIVER_CFG80211 )
	{
		if(pmlmepriv->p2p_assoc_req_ie && pmlmepriv->p2p_assoc_req_ie_len>0)
		{
			_rtw_memcpy(pframe, pmlmepriv->p2p_assoc_req_ie, pmlmepriv->p2p_assoc_req_ie_len);
			pframe += pmlmepriv->p2p_assoc_req_ie_len;
			pattrib->pktlen += pmlmepriv->p2p_assoc_req_ie_len;
		}
	}
	else
#endif //CONFIG_IOCTL_CFG80211
	{
		if(!rtw_p2p_chk_state(pwdinfo, P2P_STATE_NONE) && !rtw_p2p_chk_state(pwdinfo, P2P_STATE_IDLE))
		{
			//	Should add the P2P IE in the association request frame.	
			//	P2P OUI
			
			p2pielen = 0;
			p2pie[ p2pielen++ ] = 0x50;
			p2pie[ p2pielen++ ] = 0x6F;
			p2pie[ p2pielen++ ] = 0x9A;
			p2pie[ p2pielen++ ] = 0x09;	//	WFA P2P v1.0

			//	Commented by Albert 20101109
			//	According to the P2P Specification, the association request frame should contain 3 P2P attributes
			//	1. P2P Capability
			//	2. Extended Listen Timing
			//	3. Device Info
			//	Commented by Albert 20110516
			//	4. P2P Interface

			//	P2P Capability
			//	Type:
			p2pie[ p2pielen++ ] = P2P_ATTR_CAPABILITY;

			//	Length:
			*(u16*) ( p2pie + p2pielen ) = cpu_to_le16( 0x0002 );
			p2pielen += 2;

			//	Value:
			//	Device Capability Bitmap, 1 byte
			p2pie[ p2pielen++ ] = DMP_P2P_DEVCAP_SUPPORT;

			//	Group Capability Bitmap, 1 byte
			if ( pwdinfo->persistent_supported )
				p2pie[ p2pielen++ ] = P2P_GRPCAP_PERSISTENT_GROUP | DMP_P2P_GRPCAP_SUPPORT;
			else
				p2pie[ p2pielen++ ] = DMP_P2P_GRPCAP_SUPPORT;

			//	Extended Listen Timing
			//	Type:
			p2pie[ p2pielen++ ] = P2P_ATTR_EX_LISTEN_TIMING;

			//	Length:
			*(u16*) ( p2pie + p2pielen ) = cpu_to_le16( 0x0004 );
			p2pielen += 2;

			//	Value:
			//	Availability Period
			*(u16*) ( p2pie + p2pielen ) = cpu_to_le16( 0xFFFF );
			p2pielen += 2;

			//	Availability Interval
			*(u16*) ( p2pie + p2pielen ) = cpu_to_le16( 0xFFFF );
			p2pielen += 2;

			//	Device Info
			//	Type:
			p2pie[ p2pielen++ ] = P2P_ATTR_DEVICE_INFO;

			//	Length:
			//	21 -> P2P Device Address (6bytes) + Config Methods (2bytes) + Primary Device Type (8bytes) 
			//	+ NumofSecondDevType (1byte) + WPS Device Name ID field (2bytes) + WPS Device Name Len field (2bytes)
			*(u16*) ( p2pie + p2pielen ) = cpu_to_le16( 21 + pwdinfo->device_name_len );
			p2pielen += 2;

			//	Value:
			//	P2P Device Address
			_rtw_memcpy(p2pie + p2pielen, adapter_mac_addr(padapter), ETH_ALEN);
			p2pielen += ETH_ALEN;

			//	Config Method
			//	This field should be big endian. Noted by P2P specification.
			if ( ( pwdinfo->ui_got_wps_info == P2P_GOT_WPSINFO_PEER_DISPLAY_PIN ) ||
				( pwdinfo->ui_got_wps_info == P2P_GOT_WPSINFO_SELF_DISPLAY_PIN ) )
			{
				*(u16*) ( p2pie + p2pielen ) = cpu_to_be16( WPS_CONFIG_METHOD_DISPLAY );
			}
			else
			{
				*(u16*) ( p2pie + p2pielen ) = cpu_to_be16( WPS_CONFIG_METHOD_PBC );
			}

			p2pielen += 2;

			//	Primary Device Type
			//	Category ID
			*(u16*) ( p2pie + p2pielen ) = cpu_to_be16( WPS_PDT_CID_MULIT_MEDIA );
			p2pielen += 2;

			//	OUI
			*(u32*) ( p2pie + p2pielen ) = cpu_to_be32( WPSOUI );
			p2pielen += 4;

			//	Sub Category ID
			*(u16*) ( p2pie + p2pielen ) = cpu_to_be16( WPS_PDT_SCID_MEDIA_SERVER );
			p2pielen += 2;

			//	Number of Secondary Device Types
			p2pie[ p2pielen++ ] = 0x00;	//	No Secondary Device Type List

			//	Device Name
			//	Type:
			*(u16*) ( p2pie + p2pielen ) = cpu_to_be16( WPS_ATTR_DEVICE_NAME );
			p2pielen += 2;

			//	Length:
			*(u16*) ( p2pie + p2pielen ) = cpu_to_be16( pwdinfo->device_name_len );
			p2pielen += 2;

			//	Value:
			_rtw_memcpy( p2pie + p2pielen, pwdinfo->device_name, pwdinfo->device_name_len );
			p2pielen += pwdinfo->device_name_len;
		
			//	P2P Interface
			//	Type:
			p2pie[ p2pielen++ ] = P2P_ATTR_INTERFACE;
			
			//	Length:
			*(u16*) ( p2pie + p2pielen ) = cpu_to_le16( 0x000D );
			p2pielen += 2;
			
			//	Value:
			_rtw_memcpy( p2pie + p2pielen, pwdinfo->device_addr, ETH_ALEN );	//	P2P Device Address
			p2pielen += ETH_ALEN;

			p2pie[ p2pielen++ ] = 1;	//	P2P Interface Address Count
			
			_rtw_memcpy( p2pie + p2pielen, pwdinfo->device_addr, ETH_ALEN );	//	P2P Interface Address List
			p2pielen += ETH_ALEN;
		
			pframe = rtw_set_ie(pframe, _VENDOR_SPECIFIC_IE_, p2pielen, (unsigned char *) p2pie, &pattrib->pktlen );

#ifdef CONFIG_WFD
			//wfdielen = build_assoc_req_wfd_ie(pwdinfo, pframe);
			//pframe += wfdielen;
			//pattrib->pktlen += wfdielen;
#endif //CONFIG_WFD
		}
	}
