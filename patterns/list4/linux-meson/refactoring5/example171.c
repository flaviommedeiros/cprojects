#ifdef CONFIG_CONCURRENT_MODE
if ( check_buddy_fwstate(padapter, _FW_LINKED ) )
					{
						DBG_871X( "[%s] desired channel NOT Found!\n", __FUNCTION__ );
						result = P2P_STATUS_FAIL_NO_COMMON_CH;
						rtw_p2p_set_state(pwdinfo, P2P_STATE_GONEGO_FAIL);
						break;
					}
					else
#endif //CONFIG_CONCURRENT_MODE
					{
						u8 operatingch_info[5] = { 0x00 }, peer_operating_ch = 0;
						attr_contentlen = 0;

						if ( rtw_get_p2p_attr_content(p2p_ie, p2p_ielen, P2P_ATTR_OPERATING_CH, operatingch_info, &attr_contentlen) )
						{		
							peer_operating_ch = operatingch_info[4];
						}

						if ( rtw_p2p_is_channel_list_ok( peer_operating_ch, 
														ch_list_inclusioned, ch_num_inclusioned) )
						{
							/**
							 *	Change our operating channel as peer's for compatibility.
							 */
							pwdinfo->operating_channel = peer_operating_ch;
							DBG_871X( "[%s] Change op ch to %02x as peer's\n", __FUNCTION__, pwdinfo->operating_channel);
						}
						else
						{
							// Take first channel of ch_list_inclusioned as operating channel
							pwdinfo->operating_channel = ch_list_inclusioned[0];
							DBG_871X( "[%s] Change op ch to %02x\n", __FUNCTION__, pwdinfo->operating_channel);
						}
					}
