#ifdef CONFIG_IOCTL_CFG80211
if(adapter_wdev_data(padapter)->p2p_enabled && pwdinfo->driver_interface == DRIVER_CFG80211 )
	{
		if( pmlmepriv->wps_probe_resp_ie != NULL && pmlmepriv->p2p_probe_resp_ie != NULL )
		{
			//WPS IE
			_rtw_memcpy(pframe, pmlmepriv->wps_probe_resp_ie, pmlmepriv->wps_probe_resp_ie_len);
			pattrib->pktlen += pmlmepriv->wps_probe_resp_ie_len;
			pframe += pmlmepriv->wps_probe_resp_ie_len;

			//P2P IE
			_rtw_memcpy(pframe, pmlmepriv->p2p_probe_resp_ie, pmlmepriv->p2p_probe_resp_ie_len);
			pattrib->pktlen += pmlmepriv->p2p_probe_resp_ie_len;
			pframe += pmlmepriv->p2p_probe_resp_ie_len;
		}
	}
	else
#endif //CONFIG_IOCTL_CFG80211		
	{

		//	Todo: WPS IE
		//	Noted by Albert 20100907
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

#ifdef CONFIG_INTEL_WIDI
		//	Commented by Kurt
		//	Appended WiDi info. only if we did issued_probereq_widi(), and then we saved ven. ext. in pmlmepriv->sa_ext.
		if(  _rtw_memcmp(pmlmepriv->sa_ext, zero_array_check, L2SDTA_SERVICE_VE_LEN) == _FALSE 
			|| pmlmepriv->num_p2p_sdt != 0 )
		{
			//Sec dev type
			*(u16*) ( wpsie + wpsielen ) = cpu_to_be16( WPS_ATTR_SEC_DEV_TYPE_LIST );
			wpsielen += 2;

			//	Length:
			*(u16*) ( wpsie + wpsielen ) = cpu_to_be16( 0x0008 );
			wpsielen += 2;

			//	Value:
			//	Category ID
			*(u16*) ( wpsie + wpsielen ) = cpu_to_be16( WPS_PDT_CID_DISPLAYS );
			wpsielen += 2;

			//	OUI
			*(u32*) ( wpsie + wpsielen ) = cpu_to_be32( INTEL_DEV_TYPE_OUI );
			wpsielen += 4;

			*(u16*) ( wpsie + wpsielen ) = cpu_to_be16( WPS_PDT_SCID_WIDI_CONSUMER_SINK );
			wpsielen += 2;

			if(  _rtw_memcmp(pmlmepriv->sa_ext, zero_array_check, L2SDTA_SERVICE_VE_LEN) == _FALSE )
			{
				//	Vendor Extension
				_rtw_memcpy( wpsie + wpsielen, pmlmepriv->sa_ext, L2SDTA_SERVICE_VE_LEN );
				wpsielen += L2SDTA_SERVICE_VE_LEN;
			}
		}
#endif //CONFIG_INTEL_WIDI

		//	WiFi Simple Config State
		//	Type:
		*(u16*) ( wpsie + wpsielen ) = cpu_to_be16( WPS_ATTR_SIMPLE_CONF_STATE );
		wpsielen += 2;

		//	Length:
		*(u16*) ( wpsie + wpsielen ) = cpu_to_be16( 0x0001 );
		wpsielen += 2;

		//	Value:
		wpsie[wpsielen++] = WPS_WSC_STATE_NOT_CONFIG;	//	Not Configured.

		//	Response Type
		//	Type:
		*(u16*) ( wpsie + wpsielen ) = cpu_to_be16( WPS_ATTR_RESP_TYPE );
		wpsielen += 2;

		//	Length:
		*(u16*) ( wpsie + wpsielen ) = cpu_to_be16( 0x0001 );
		wpsielen += 2;

		//	Value:
		wpsie[wpsielen++] = WPS_RESPONSE_TYPE_8021X;

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

		//	Manufacturer
		//	Type:
		*(u16*) ( wpsie + wpsielen ) = cpu_to_be16( WPS_ATTR_MANUFACTURER );
		wpsielen += 2;

		//	Length:
		*(u16*) ( wpsie + wpsielen ) = cpu_to_be16( 0x0007 );
		wpsielen += 2;

		//	Value:
		_rtw_memcpy( wpsie + wpsielen, "Realtek", 7 );
		wpsielen += 7;

		//	Model Name
		//	Type:
		*(u16*) ( wpsie + wpsielen ) = cpu_to_be16( WPS_ATTR_MODEL_NAME );
		wpsielen += 2;

		//	Length:
		*(u16*) ( wpsie + wpsielen ) = cpu_to_be16( 0x0006 );
		wpsielen += 2;	

		//	Value:
		_rtw_memcpy( wpsie + wpsielen, "8192CU", 6 );
		wpsielen += 6;

		//	Model Number
		//	Type:
		*(u16*) ( wpsie + wpsielen ) = cpu_to_be16( WPS_ATTR_MODEL_NUMBER );
		wpsielen += 2;

		//	Length:
		*(u16*) ( wpsie + wpsielen ) = cpu_to_be16( 0x0001 );
		wpsielen += 2;

		//	Value:
		wpsie[ wpsielen++ ] = 0x31;		//	character 1

		//	Serial Number
		//	Type:
		*(u16*) ( wpsie + wpsielen ) = cpu_to_be16( WPS_ATTR_SERIAL_NUMBER );
		wpsielen += 2;

		//	Length:
		*(u16*) ( wpsie + wpsielen ) = cpu_to_be16( ETH_ALEN );
		wpsielen += 2;

		//	Value:
		_rtw_memcpy( wpsie + wpsielen, "123456" , ETH_ALEN );
		wpsielen += ETH_ALEN;

		//	Primary Device Type
		//	Type:
		*(u16*) ( wpsie + wpsielen ) = cpu_to_be16( WPS_ATTR_PRIMARY_DEV_TYPE );
		wpsielen += 2;

		//	Length:
		*(u16*) ( wpsie + wpsielen ) = cpu_to_be16( 0x0008 );
		wpsielen += 2;

		//	Value:
		//	Category ID
		*(u16*) ( wpsie + wpsielen ) = cpu_to_be16( WPS_PDT_CID_MULIT_MEDIA );
		wpsielen += 2;

		//	OUI
		*(u32*) ( wpsie + wpsielen ) = cpu_to_be32( WPSOUI );
		wpsielen += 4;

		//	Sub Category ID
		*(u16*) ( wpsie + wpsielen ) = cpu_to_be16( WPS_PDT_SCID_MEDIA_SERVER );
		wpsielen += 2;

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
		

		pframe = rtw_set_ie(pframe, _VENDOR_SPECIFIC_IE_, wpsielen, (unsigned char *) wpsie, &pattrib->pktlen );
		

		p2pielen = build_probe_resp_p2p_ie(pwdinfo, pframe);
		pframe += p2pielen;
		pattrib->pktlen += p2pielen;
	}
