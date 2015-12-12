#ifdef CONFIG_IOCTL_CFG80211
if(pwdinfo->driver_interface == DRIVER_CFG80211 )
			{
				if(pmlmepriv->wps_beacon_ie && pmlmepriv->wps_beacon_ie_len>0)
				{
					_rtw_memcpy(pframe, cur_network->IEs, wps_offset);
					pframe += wps_offset;
					pktlen += wps_offset;

					_rtw_memcpy(pframe, pmlmepriv->wps_beacon_ie, pmlmepriv->wps_beacon_ie_len);
					pframe += pmlmepriv->wps_beacon_ie_len;
					pktlen += pmlmepriv->wps_beacon_ie_len;

					//copy remainder_ie to pframe
					_rtw_memcpy(pframe, premainder_ie, remainder_ielen);
					pframe += remainder_ielen;		
					pktlen += remainder_ielen;
				}
				else
				{
					_rtw_memcpy(pframe, cur_network->IEs, cur_network->IELength);
					pframe += cur_network->IELength;
					pktlen += cur_network->IELength;
				}
			}
			else
#endif //CONFIG_IOCTL_CFG80211
			{
				pframe_wscie = pframe + wps_offset;
				_rtw_memcpy(pframe, cur_network->IEs, wps_offset+wpsielen);			
				pframe += (wps_offset + wpsielen);		
				pktlen += (wps_offset + wpsielen);

				//now pframe is end of wsc ie, insert Primary Device Type & Device Name
				//	Primary Device Type
				//	Type:
				*(u16*) ( pframe + insert_len) = cpu_to_be16( WPS_ATTR_PRIMARY_DEV_TYPE );
				insert_len += 2;
				
				//	Length:
				*(u16*) ( pframe + insert_len ) = cpu_to_be16( 0x0008 );
				insert_len += 2;
				
				//	Value:
				//	Category ID
				*(u16*) ( pframe + insert_len ) = cpu_to_be16( WPS_PDT_CID_MULIT_MEDIA );
				insert_len += 2;

				//	OUI
				*(u32*) ( pframe + insert_len ) = cpu_to_be32( WPSOUI );
				insert_len += 4;

				//	Sub Category ID
				*(u16*) ( pframe + insert_len ) = cpu_to_be16( WPS_PDT_SCID_MEDIA_SERVER );
				insert_len += 2;


				//	Device Name
				//	Type:
				*(u16*) ( pframe + insert_len ) = cpu_to_be16( WPS_ATTR_DEVICE_NAME );
				insert_len += 2;

				//	Length:
				*(u16*) ( pframe + insert_len ) = cpu_to_be16( pwdinfo->device_name_len );
				insert_len += 2;

				//	Value:
				_rtw_memcpy( pframe + insert_len, pwdinfo->device_name, pwdinfo->device_name_len );
				insert_len += pwdinfo->device_name_len;


				//update wsc ie length
				*(pframe_wscie+1) = (wpsielen -2) + insert_len;

				//pframe move to end
				pframe+=insert_len;
				pktlen += insert_len;

				//copy remainder_ie to pframe
				_rtw_memcpy(pframe, premainder_ie, remainder_ielen);
				pframe += remainder_ielen;		
				pktlen += remainder_ielen;
			}
