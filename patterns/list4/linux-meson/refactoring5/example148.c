#ifdef CONFIG_IOCTL_CFG80211
if(adapter_wdev_data(padapter)->p2p_enabled && pwdinfo->driver_interface == DRIVER_CFG80211 )
	{
		if( pmlmepriv->wps_probe_req_ie != NULL && pmlmepriv->p2p_probe_req_ie != NULL )
		{
			//WPS IE
			_rtw_memcpy(pframe, pmlmepriv->wps_probe_req_ie, pmlmepriv->wps_probe_req_ie_len);
			pattrib->pktlen += pmlmepriv->wps_probe_req_ie_len;
			pframe += pmlmepriv->wps_probe_req_ie_len;

			//P2P IE
			_rtw_memcpy(pframe, pmlmepriv->p2p_probe_req_ie, pmlmepriv->p2p_probe_req_ie_len);
			pattrib->pktlen += pmlmepriv->p2p_probe_req_ie_len;
			pframe += pmlmepriv->p2p_probe_req_ie_len;
		}
	}
	else
#endif //CONFIG_IOCTL_CFG80211
	{

		//	WPS IE
		//	Noted by Albert 20110221
		//	According to the WPS specification, all the WPS attribute is presented by Big Endian.

		wpsielen = 0;
		//	WPS OUI
		*(u32*) ( wpsie ) = cpu_to_be32( WPSOUI );
		wpsielen += 4;

		//	WPS version
		//	Type:
		*(u16*) ( wpsie + wpsielen ) = cpu_to_be16( WPS_ATTR_VER1 );
		wpsielen += 2;

		//	Length:
		*(u16*) ( wpsie + wpsielen ) = cpu_to_be16( 0x0001 );
		wpsielen += 2;

		//	Value:
		wpsie[wpsielen++] = WPS_VERSION_1;	//	Version 1.0

		if( pmlmepriv->wps_probe_req_ie == NULL )
		{
			//	UUID-E
			//	Type:
			*(u16*) ( wpsie + wpsielen ) = cpu_to_be16( WPS_ATTR_UUID_E );
			wpsielen += 2;

			//	Length:
			*(u16*) ( wpsie + wpsielen ) = cpu_to_be16( 0x0010 );
			wpsielen += 2;

			//	Value:
			if (pwdinfo->external_uuid == 0) {
				_rtw_memset( wpsie + wpsielen, 0x0, 16 );
				_rtw_memcpy(wpsie + wpsielen, mac, ETH_ALEN);
			} else {
				_rtw_memcpy( wpsie + wpsielen, pwdinfo->uuid, 0x10 );
			}
			wpsielen += 0x10;

			//	Config Method
			//	Type:
			*(u16*) ( wpsie + wpsielen ) = cpu_to_be16( WPS_ATTR_CONF_METHOD );
			wpsielen += 2;

			//	Length:
			*(u16*) ( wpsie + wpsielen ) = cpu_to_be16( 0x0002 );
			wpsielen += 2;

			//	Value:
			*(u16*) ( wpsie + wpsielen ) = cpu_to_be16( pwdinfo->supported_wps_cm );
			wpsielen += 2;
		}

		//	Device Name
		//	Type:
		*(u16*) ( wpsie + wpsielen ) = cpu_to_be16( WPS_ATTR_DEVICE_NAME );
		wpsielen += 2;

		//	Length:
		*(u16*) ( wpsie + wpsielen ) = cpu_to_be16( pwdinfo->device_name_len );
		wpsielen += 2;

		//	Value:
		_rtw_memcpy( wpsie + wpsielen, pwdinfo->device_name, pwdinfo->device_name_len );
		wpsielen += pwdinfo->device_name_len;

		//	Primary Device Type
		//	Type:
		*(u16*) ( wpsie + wpsielen ) = cpu_to_be16( WPS_ATTR_PRIMARY_DEV_TYPE );
		wpsielen += 2;

		//	Length:
		*(u16*) ( wpsie + wpsielen ) = cpu_to_be16( 0x0008 );
		wpsielen += 2;

		//	Value:
		//	Category ID
		*(u16*) ( wpsie + wpsielen ) = cpu_to_be16( WPS_PDT_CID_RTK_WIDI );
		wpsielen += 2;

		//	OUI
		*(u32*) ( wpsie + wpsielen ) = cpu_to_be32( WPSOUI );
		wpsielen += 4;

		//	Sub Category ID
		*(u16*) ( wpsie + wpsielen ) = cpu_to_be16( WPS_PDT_SCID_RTK_DMP );
		wpsielen += 2;

		//	Device Password ID
		//	Type:
		*(u16*) ( wpsie + wpsielen ) = cpu_to_be16( WPS_ATTR_DEVICE_PWID );
		wpsielen += 2;

		//	Length:
		*(u16*) ( wpsie + wpsielen ) = cpu_to_be16( 0x0002 );
		wpsielen += 2;

		//	Value:
		*(u16*) ( wpsie + wpsielen ) = cpu_to_be16( WPS_DPID_REGISTRAR_SPEC );	//	Registrar-specified
		wpsielen += 2;	

		pframe = rtw_set_ie(pframe, _VENDOR_SPECIFIC_IE_, wpsielen, (unsigned char *) wpsie, &pattrib->pktlen );
		
		//	P2P OUI
		p2pielen = 0;
		p2pie[ p2pielen++ ] = 0x50;
		p2pie[ p2pielen++ ] = 0x6F;
		p2pie[ p2pielen++ ] = 0x9A;
		p2pie[ p2pielen++ ] = 0x09;	//	WFA P2P v1.0

		//	Commented by Albert 20110221
		//	According to the P2P Specification, the probe request frame should contain 5 P2P attributes
		//	1. P2P Capability
		//	2. P2P Device ID if this probe request wants to find the specific P2P device
		//	3. Listen Channel
		//	4. Extended Listen Timing
		//	5. Operating Channel if this WiFi is working as the group owner now

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

		//	Listen Channel
		//	Type:
		p2pie[ p2pielen++ ] = P2P_ATTR_LISTEN_CH;

		//	Length:
		*(u16*) ( p2pie + p2pielen ) = cpu_to_le16( 0x0005 );
		p2pielen += 2;

		//	Value:
		//	Country String
		p2pie[ p2pielen++ ] = 'X';
		p2pie[ p2pielen++ ] = 'X';
		
		//	The third byte should be set to 0x04.
		//	Described in the "Operating Channel Attribute" section.
		p2pie[ p2pielen++ ] = 0x04;

		//	Operating Class
		p2pie[ p2pielen++ ] = 0x51;	//	Copy from SD7
		
		//	Channel Number
		p2pie[ p2pielen++ ] = pwdinfo->listen_channel;	//	listen channel
		

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

		if ( rtw_p2p_chk_role(pwdinfo, P2P_ROLE_GO) )
		{
			//	Operating Channel (if this WiFi is working as the group owner now)
			//	Type:
			p2pie[ p2pielen++ ] = P2P_ATTR_OPERATING_CH;

			//	Length:
			*(u16*) ( p2pie + p2pielen ) = cpu_to_le16( 0x0005 );
			p2pielen += 2;

			//	Value:
			//	Country String
			p2pie[ p2pielen++ ] = 'X';
			p2pie[ p2pielen++ ] = 'X';
		
			//	The third byte should be set to 0x04.
			//	Described in the "Operating Channel Attribute" section.
			p2pie[ p2pielen++ ] = 0x04;

			//	Operating Class
			p2pie[ p2pielen++ ] = 0x51;	//	Copy from SD7
		
			//	Channel Number
			p2pie[ p2pielen++ ] = pwdinfo->operating_channel;	//	operating channel number
			
		}
		
		pframe = rtw_set_ie(pframe, _VENDOR_SPECIFIC_IE_, p2pielen, (unsigned char *) p2pie, &pattrib->pktlen );	

	}
