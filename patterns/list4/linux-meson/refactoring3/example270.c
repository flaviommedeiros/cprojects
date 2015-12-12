switch(minor_cmd)
			{
				case 0x0:
					DBG_871X("fwstate=0x%x\n", get_fwstate(pmlmepriv));
					break;
				case 0x01:
					DBG_871X("auth_alg=0x%x, enc_alg=0x%x, auth_type=0x%x, enc_type=0x%x\n", 
						psecuritypriv->dot11AuthAlgrthm, psecuritypriv->dot11PrivacyAlgrthm,
						psecuritypriv->ndisauthtype, psecuritypriv->ndisencryptstatus);
					break;
				case 0x02:
					DBG_871X("pmlmeinfo->state=0x%x\n", pmlmeinfo->state);
					DBG_871X("DrvBcnEarly=%d\n", pmlmeext->DrvBcnEarly);
					DBG_871X("DrvBcnTimeOut=%d\n", pmlmeext->DrvBcnTimeOut);
					break;
				case 0x03:
					DBG_871X("qos_option=%d\n", pmlmepriv->qospriv.qos_option);
#ifdef CONFIG_80211N_HT
					DBG_871X("ht_option=%d\n", pmlmepriv->htpriv.ht_option);
#endif //CONFIG_80211N_HT
					break;
				case 0x04:
					DBG_871X("cur_ch=%d\n", pmlmeext->cur_channel);
					DBG_871X("cur_bw=%d\n", pmlmeext->cur_bwmode);
					DBG_871X("cur_ch_off=%d\n", pmlmeext->cur_ch_offset);

					DBG_871X("oper_ch=%d\n", rtw_get_oper_ch(padapter));
					DBG_871X("oper_bw=%d\n", rtw_get_oper_bw(padapter));
					DBG_871X("oper_ch_offet=%d\n", rtw_get_oper_choffset(padapter));
				
					break;
				case 0x05:
					psta = rtw_get_stainfo(pstapriv, cur_network->network.MacAddress);
					if(psta)
					{
						DBG_871X("SSID=%s\n", cur_network->network.Ssid.Ssid);
						DBG_871X("sta's macaddr:" MAC_FMT "\n", MAC_ARG(psta->hwaddr));
						DBG_871X("cur_channel=%d, cur_bwmode=%d, cur_ch_offset=%d\n", pmlmeext->cur_channel, pmlmeext->cur_bwmode, pmlmeext->cur_ch_offset);
						DBG_871X("rtsen=%d, cts2slef=%d\n", psta->rtsen, psta->cts2self);
						DBG_871X("state=0x%x, aid=%d, macid=%d, raid=%d\n", psta->state, psta->aid, psta->mac_id, psta->raid);
#ifdef CONFIG_80211N_HT
						DBG_871X("qos_en=%d, ht_en=%d, init_rate=%d\n", psta->qos_option, psta->htpriv.ht_option, psta->init_rate);
						DBG_871X("bwmode=%d, ch_offset=%d, sgi_20m=%d,sgi_40m=%d\n", psta->bw_mode, psta->htpriv.ch_offset, psta->htpriv.sgi_20m, psta->htpriv.sgi_40m);
						DBG_871X("ampdu_enable = %d\n", psta->htpriv.ampdu_enable);	
						DBG_871X("agg_enable_bitmap=%x, candidate_tid_bitmap=%x\n", psta->htpriv.agg_enable_bitmap, psta->htpriv.candidate_tid_bitmap);
#endif //CONFIG_80211N_HT

						sta_rx_reorder_ctl_dump(RTW_DBGDUMP, psta);
					}
					else
					{							
						DBG_871X("can't get sta's macaddr, cur_network's macaddr:" MAC_FMT "\n", MAC_ARG(cur_network->network.MacAddress));
					}					
					break;
				case 0x06:
					{						
					}
					break;
				case 0x07:
					DBG_871X("bSurpriseRemoved=%d, bDriverStopped=%d\n", 
						padapter->bSurpriseRemoved, padapter->bDriverStopped);
					break;
				case 0x08:
					{
						struct xmit_priv *pxmitpriv = &padapter->xmitpriv;
						struct recv_priv  *precvpriv = &padapter->recvpriv;
						
						DBG_871X("free_xmitbuf_cnt=%d, free_xmitframe_cnt=%d"
							", free_xmit_extbuf_cnt=%d, free_xframe_ext_cnt=%d"
							", free_recvframe_cnt=%d\n",
							pxmitpriv->free_xmitbuf_cnt, pxmitpriv->free_xmitframe_cnt,
							pxmitpriv->free_xmit_extbuf_cnt, pxmitpriv->free_xframe_ext_cnt,
							precvpriv->free_recvframe_cnt);
						#ifdef CONFIG_USB_HCI
						DBG_871X("rx_urb_pending_cn=%d\n", ATOMIC_READ(&(precvpriv->rx_pending_cnt)));
						#endif
					}
					break;	
				case 0x09:
					{
						int i;
						_list	*plist, *phead;
						
#ifdef CONFIG_AP_MODE
						DBG_871X("sta_dz_bitmap=0x%x, tim_bitmap=0x%x\n", pstapriv->sta_dz_bitmap, pstapriv->tim_bitmap);
#endif						
						_enter_critical_bh(&pstapriv->sta_hash_lock, &irqL);

						for(i=0; i< NUM_STA; i++)
						{
							phead = &(pstapriv->sta_hash[i]);
							plist = get_next(phead);
		
							while ((rtw_end_of_queue_search(phead, plist)) == _FALSE)
							{
								psta = LIST_CONTAINOR(plist, struct sta_info, hash_list);

								plist = get_next(plist);

								if(extra_arg == psta->aid)
								{
									DBG_871X("sta's macaddr:" MAC_FMT "\n", MAC_ARG(psta->hwaddr));
									DBG_871X("rtsen=%d, cts2slef=%d\n", psta->rtsen, psta->cts2self);
									DBG_871X("state=0x%x, aid=%d, macid=%d, raid=%d\n", psta->state, psta->aid, psta->mac_id, psta->raid);
#ifdef CONFIG_80211N_HT
									DBG_871X("qos_en=%d, ht_en=%d, init_rate=%d\n", psta->qos_option, psta->htpriv.ht_option, psta->init_rate);	
									DBG_871X("bwmode=%d, ch_offset=%d, sgi_20m=%d,sgi_40m=%d\n", psta->bw_mode, psta->htpriv.ch_offset, psta->htpriv.sgi_20m, psta->htpriv.sgi_40m);
									DBG_871X("ampdu_enable = %d\n", psta->htpriv.ampdu_enable);									
									DBG_871X("agg_enable_bitmap=%x, candidate_tid_bitmap=%x\n", psta->htpriv.agg_enable_bitmap, psta->htpriv.candidate_tid_bitmap);
#endif //CONFIG_80211N_HT
									
#ifdef CONFIG_AP_MODE
									DBG_871X("capability=0x%x\n", psta->capability);
									DBG_871X("flags=0x%x\n", psta->flags);
									DBG_871X("wpa_psk=0x%x\n", psta->wpa_psk);
									DBG_871X("wpa2_group_cipher=0x%x\n", psta->wpa2_group_cipher);
									DBG_871X("wpa2_pairwise_cipher=0x%x\n", psta->wpa2_pairwise_cipher);
									DBG_871X("qos_info=0x%x\n", psta->qos_info);
#endif
									DBG_871X("dot118021XPrivacy=0x%x\n", psta->dot118021XPrivacy);

									sta_rx_reorder_ctl_dump(RTW_DBGDUMP, psta);
								}							
			
							}
						}
	
						_exit_critical_bh(&pstapriv->sta_hash_lock, &irqL);

					}
					break;
				case 0x0a:
					{
						int max_mac_id = 0;
						max_mac_id = rtw_search_max_mac_id( padapter);
						printk("%s ==> max_mac_id = %d \n",__FUNCTION__,max_mac_id);
					}	
					break;
				case 0x0b: //Enable=1, Disable=0 driver control vrtl_carrier_sense.
					{
						//u8 driver_vcs_en; //Enable=1, Disable=0 driver control vrtl_carrier_sense.
						//u8 driver_vcs_type;//force 0:disable VCS, 1:RTS-CTS, 2:CTS-to-self when vcs_en=1.

						if(arg == 0){
							DBG_871X("disable driver ctrl vcs\n");						
							padapter->driver_vcs_en = 0;					
						}
						else if(arg == 1){							
							DBG_871X("enable driver ctrl vcs = %d\n", extra_arg);
							padapter->driver_vcs_en = 1;
	
							if(extra_arg>2)
								padapter->driver_vcs_type = 1;						
							else
								padapter->driver_vcs_type = extra_arg;
						}
					}
					break;
				case 0x0c://dump rx/tx packet
					{
						if(arg == 0){
							DBG_871X("dump rx packet (%d)\n",extra_arg);						
							//pHalData->bDumpRxPkt =extra_arg;						
							rtw_hal_set_def_var(padapter, HAL_DEF_DBG_DUMP_RXPKT, &(extra_arg));
						}
						else if(arg==1){
							DBG_871X("dump tx packet (%d)\n",extra_arg);						
							rtw_hal_set_def_var(padapter, HAL_DEF_DBG_DUMP_TXPKT, &(extra_arg));
						}
					}
					break;
#if 0				
				case 0x0d://dump cam
					{
						//u8 entry = (u8) extra_arg;
						u8 entry=0;
						//dump cam
						for(entry=0;entry<32;entry++)
							read_cam(padapter,entry);
					}				
					break;
#endif
				case 0x0e:
					{
						if(arg == 0){
							DBG_871X("disable driver ctrl rx_ampdu_factor\n");						
							padapter->driver_rx_ampdu_factor = 0xFF;
						}
						else if(arg == 1){
							
							DBG_871X("enable driver ctrl rx_ampdu_factor = %d\n", extra_arg);	
	
							if(extra_arg > 0x03)
								padapter->driver_rx_ampdu_factor = 0xFF;						
							else
								padapter->driver_rx_ampdu_factor = extra_arg;
						}					
					}
					break;
		#ifdef DBG_CONFIG_ERROR_DETECT
				case 0x0f:
						{
							if(extra_arg == 0){	
								DBG_871X("###### silent reset test.......#####\n");
								rtw_hal_sreset_reset(padapter);						
							} else {
								HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(padapter);
								struct sreset_priv *psrtpriv = &pHalData->srestpriv;
								psrtpriv->dbg_trigger_point = extra_arg;
							}
							
						}
					break;
				case 0x15:
					{
						struct pwrctrl_priv *pwrpriv = adapter_to_pwrctl(padapter);
						DBG_871X("==>silent resete cnts:%d\n",pwrpriv->ips_enter_cnts);
					}
					break;	
					
		#endif	

				case 0x10:// driver version display
					dump_drv_version(RTW_DBGDUMP);
					break;
				case 0x11://dump linked status
					{
						int pre_mode;
						pre_mode=padapter->bLinkInfoDump;
						// linked_info_dump(padapter,extra_arg);
						 if(extra_arg==1 || (extra_arg==0 && pre_mode==1) ) //not consider pwr_saving 0:
						{
							padapter->bLinkInfoDump = extra_arg;	
		
						}
						else if( (extra_arg==2 ) || (extra_arg==0 && pre_mode==2))//consider power_saving
						{		
						//DBG_871X("linked_info_dump =%s \n", (padapter->bLinkInfoDump)?"enable":"disable")
							linked_info_dump(padapter,extra_arg);	
						}


						 
					}					
					break;
#ifdef CONFIG_80211N_HT
				case 0x12: //set rx_stbc
				{
					struct registry_priv	*pregpriv = &padapter->registrypriv;
					// 0: disable, bit(0):enable 2.4g, bit(1):enable 5g, 0x3: enable both 2.4g and 5g
					//default is set to enable 2.4GHZ for IOT issue with bufflao's AP at 5GHZ
					if( pregpriv && (extra_arg == 0 || extra_arg == 1|| extra_arg == 2 || extra_arg == 3))
					{
						pregpriv->rx_stbc= extra_arg;
						DBG_871X("set rx_stbc=%d\n",pregpriv->rx_stbc);
					}
					else
						DBG_871X("get rx_stbc=%d\n",pregpriv->rx_stbc);
					
				}
				break;
				case 0x13: //set ampdu_enable
				{
					struct registry_priv	*pregpriv = &padapter->registrypriv;
					// 0: disable, 0x1:enable (but wifi_spec should be 0), 0x2: force enable (don't care wifi_spec)
					if( pregpriv && extra_arg < 3 )
					{
						pregpriv->ampdu_enable= extra_arg;
						DBG_871X("set ampdu_enable=%d\n",pregpriv->ampdu_enable);
					}
					else
						DBG_871X("get ampdu_enable=%d\n",pregpriv->ampdu_enable);
					
				}
				break;
#endif
				case 0x14: //get wifi_spec
				{
					struct registry_priv	*pregpriv = &padapter->registrypriv;
					DBG_871X("get wifi_spec=%d\n",pregpriv->wifi_spec);
					
				}
				break;
				case 0x16:
				{
					if(arg == 0xff){
						rtw_odm_dbg_comp_msg(RTW_DBGDUMP,padapter);
					}
					else{
						u64 dbg_comp = (u64)extra_arg;
						rtw_odm_dbg_comp_set(padapter, dbg_comp);
					}
				}
					break;
#ifdef DBG_FIXED_CHAN
				case 0x17:
					{
						struct mlme_ext_priv	*pmlmeext = &(padapter->mlmeextpriv);						
						printk("===>  Fixed channel to %d \n",extra_arg);
						pmlmeext->fixed_chan = extra_arg;	
						
					}
					break;
#endif
				case 0x18:
					{
						printk("===>  Switch USB Mode %d \n",extra_arg);
						rtw_hal_set_hwreg(padapter, HW_VAR_USB_MODE, (u8 *)&extra_arg);
					}
					break;
#ifdef CONFIG_80211N_HT			
				case 0x19:
					{
						struct registry_priv	*pregistrypriv = &padapter->registrypriv;
						// extra_arg :
						// BIT0: Enable VHT LDPC Rx, BIT1: Enable VHT LDPC Tx, 
						// BIT4: Enable HT LDPC Rx, BIT5: Enable HT LDPC Tx
						if(arg == 0){
							DBG_871X("driver disable LDPC\n");						
							pregistrypriv->ldpc_cap = 0x00;
						}
						else if(arg == 1){							
							DBG_871X("driver set LDPC cap = 0x%x\n", extra_arg);
							pregistrypriv->ldpc_cap = (u8)(extra_arg&0x33);						
						}						
					}
                                        break;
				case 0x1a:
					{
						struct registry_priv	*pregistrypriv = &padapter->registrypriv;
						// extra_arg :
						// BIT0: Enable VHT STBC Rx, BIT1: Enable VHT STBC Tx, 
						// BIT4: Enable HT STBC Rx, BIT5: Enable HT STBC Tx
						if(arg == 0){
							DBG_871X("driver disable STBC\n");						
							pregistrypriv->stbc_cap = 0x00;
						}
						else if(arg == 1){							
							DBG_871X("driver set STBC cap = 0x%x\n", extra_arg);
							pregistrypriv->stbc_cap = (u8)(extra_arg&0x33);						
						}						
					}
                                        break;
#endif //CONFIG_80211N_HT
				case 0x1b:
					{	
						struct registry_priv	*pregistrypriv = &padapter->registrypriv;
						
						if(arg == 0){
							DBG_871X("disable driver ctrl max_rx_rate, reset to default_rate_set\n");							
							init_mlme_default_rate_set(padapter);
#ifdef CONFIG_80211N_HT						
							pregistrypriv->ht_enable = (u8)rtw_ht_enable;
#endif //CONFIG_80211N_HT
						}
						else if(arg == 1){

							int i;
							u8 max_rx_rate;						
							
							DBG_871X("enable driver ctrl max_rx_rate = 0x%x\n", extra_arg);	

							max_rx_rate = (u8)extra_arg;

							if(max_rx_rate < 0xc) // max_rx_rate < MSC0 -> B or G -> disable HT
							{
#ifdef CONFIG_80211N_HT						
								pregistrypriv->ht_enable = 0;
#endif //CONFIG_80211N_HT
								for(i=0; i<NumRates; i++)
								{
									if(pmlmeext->datarate[i] > max_rx_rate)
										pmlmeext->datarate[i] = 0xff;									
								}	

							}
#ifdef CONFIG_80211N_HT	
							else if(max_rx_rate < 0x1c) // mcs0~mcs15
							{
								u32 mcs_bitmap=0x0;
													
								for(i=0; i<((max_rx_rate+1)-0xc); i++)
									mcs_bitmap |= BIT(i);
								
								set_mcs_rate_by_mask(pmlmeext->default_supported_mcs_set, mcs_bitmap);
							}
#endif //CONFIG_80211N_HT							
						}											
					}
                                        break;
				case 0x1c: //enable/disable driver control AMPDU Density for peer sta's rx
					{
						if(arg == 0){
							DBG_871X("disable driver ctrl ampdu density\n");						
							padapter->driver_ampdu_spacing = 0xFF;
						}
						else if(arg == 1){
							
							DBG_871X("enable driver ctrl ampdu density = %d\n", extra_arg);	
	
							if(extra_arg > 0x07)
								padapter->driver_ampdu_spacing = 0xFF;						
							else
								padapter->driver_ampdu_spacing = extra_arg;
						}
					}
					break;
#ifdef CONFIG_BACKGROUND_NOISE_MONITOR
				case 0x1e:
					{
						HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(padapter);
						PDM_ODM_T pDM_Odm = &pHalData->odmpriv;
						u8 chan = rtw_get_oper_ch(padapter);
						DBG_871X("===========================================\n");
						ODM_InbandNoise_Monitor(pDM_Odm,_TRUE,0x1e,100);
						DBG_871X("channel(%d),noise_a = %d, noise_b = %d , noise_all:%d \n", 
							chan,pDM_Odm->noise_level.noise[ODM_RF_PATH_A], 
							pDM_Odm->noise_level.noise[ODM_RF_PATH_B],
							pDM_Odm->noise_level.noise_all);
						DBG_871X("===========================================\n");
						
					}
					break;
#endif
				case 0x23:
					{
						DBG_871X("turn %s the bNotifyChannelChange Variable\n",(extra_arg==1)?"on":"off");
						padapter->bNotifyChannelChange = extra_arg;
						break;
					}
				case 0x24:
					{
#ifdef CONFIG_P2P
						DBG_871X("turn %s the bShowGetP2PState Variable\n",(extra_arg==1)?"on":"off");
						padapter->bShowGetP2PState = extra_arg;
#endif // CONFIG_P2P
						break;						
					}
#ifdef CONFIG_GPIO_API              
		            case 0x25: //Get GPIO register
		                    {
			                    /*
			                    * dbg 0x7f250000 [gpio_num], Get gpio value, gpio_num:0~7
			                    */                
                              
			                    u8 value;
			                    DBG_871X("Read GPIO Value  extra_arg = %d\n",extra_arg);
			                    value = rtw_hal_get_gpio(padapter,extra_arg);
			                    DBG_871X("Read GPIO Value = %d\n",value);                                        
			                    break;
		                    }
		            case 0x26: //Set GPIO direction
		                    {
                                       						
			                    /* dbg 0x7f26000x [y], Set gpio direction, 
			                    * x: gpio_num,4~7  y: indicate direction, 0~1  
			                    */ 
                                        
			                    int value;
			                    DBG_871X("Set GPIO Direction! arg = %d ,extra_arg=%d\n",arg ,extra_arg);
			                    value = rtw_hal_config_gpio(padapter, arg, extra_arg);
			                    DBG_871X("Set GPIO Direction %s \n",(value==-1)?"Fail!!!":"Success");
			                    break;
					}
				case 0x27: //Set GPIO output direction value
					{
						/*
						* dbg 0x7f27000x [y], Set gpio output direction value, 
 						* x: gpio_num,4~7  y: indicate direction, 0~1  
						*/ 
                                        
						int value;
						DBG_871X("Set GPIO Value! arg = %d ,extra_arg=%d\n",arg ,extra_arg);
						value = rtw_hal_set_gpio_output_value(padapter,arg,extra_arg);
						DBG_871X("Set GPIO Value %s \n",(value==-1)?"Fail!!!":"Success");
						break;
					}
#endif          
#ifdef DBG_CMD_QUEUE
				case 0x28:
					{
						dump_cmd_id = extra_arg;
						DBG_871X("dump_cmd_id:%d\n",dump_cmd_id);
					}
					break;
#endif //DBG_CMD_QUEUE
				case 0xaa:
					{
						if((extra_arg & 0x7F)> 0x3F) extra_arg = 0xFF;
						DBG_871X("chang data rate to :0x%02x\n",extra_arg);
						padapter->fix_rate = extra_arg;
					}
					break;	
				case 0xdd://registers dump , 0 for mac reg,1 for bb reg, 2 for rf reg
					{
						if(extra_arg==0){
							mac_reg_dump(RTW_DBGDUMP, padapter);
						}
						else if(extra_arg==1){
							bb_reg_dump(RTW_DBGDUMP, padapter);
						}
						else if(extra_arg==2){
							rf_reg_dump(RTW_DBGDUMP, padapter);
						}
					}
					break;		

				case 0xee:
					{
						DBG_871X(" === please control /proc  to trun on/off PHYDM func === \n");
					}
					break;

				case 0xfd:
					rtw_write8(padapter, 0xc50, arg);
					DBG_871X("wr(0xc50)=0x%x\n", rtw_read8(padapter, 0xc50));
					rtw_write8(padapter, 0xc58, arg);
					DBG_871X("wr(0xc58)=0x%x\n", rtw_read8(padapter, 0xc58));
					break;
				case 0xfe:
					DBG_871X("rd(0xc50)=0x%x\n", rtw_read8(padapter, 0xc50));
					DBG_871X("rd(0xc58)=0x%x\n", rtw_read8(padapter, 0xc58));
					break;
				case 0xff:
					{
						DBG_871X("dbg(0x210)=0x%x\n", rtw_read32(padapter, 0x210));
						DBG_871X("dbg(0x608)=0x%x\n", rtw_read32(padapter, 0x608));
						DBG_871X("dbg(0x280)=0x%x\n", rtw_read32(padapter, 0x280));
						DBG_871X("dbg(0x284)=0x%x\n", rtw_read32(padapter, 0x284));
						DBG_871X("dbg(0x288)=0x%x\n", rtw_read32(padapter, 0x288));
	
						DBG_871X("dbg(0x664)=0x%x\n", rtw_read32(padapter, 0x664));


						DBG_871X("\n");
		
						DBG_871X("dbg(0x430)=0x%x\n", rtw_read32(padapter, 0x430));
						DBG_871X("dbg(0x438)=0x%x\n", rtw_read32(padapter, 0x438));

						DBG_871X("dbg(0x440)=0x%x\n", rtw_read32(padapter, 0x440));
	
						DBG_871X("dbg(0x458)=0x%x\n", rtw_read32(padapter, 0x458));
	
						DBG_871X("dbg(0x484)=0x%x\n", rtw_read32(padapter, 0x484));
						DBG_871X("dbg(0x488)=0x%x\n", rtw_read32(padapter, 0x488));
	
						DBG_871X("dbg(0x444)=0x%x\n", rtw_read32(padapter, 0x444));
						DBG_871X("dbg(0x448)=0x%x\n", rtw_read32(padapter, 0x448));
						DBG_871X("dbg(0x44c)=0x%x\n", rtw_read32(padapter, 0x44c));
						DBG_871X("dbg(0x450)=0x%x\n", rtw_read32(padapter, 0x450));
					}
					break;
			}
