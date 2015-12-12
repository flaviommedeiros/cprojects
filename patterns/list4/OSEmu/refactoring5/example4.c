#ifdef WITH_EMU
if(cdata != NULL || update_global_key || cw_ex != NULL)
#else
			if(cdata != NULL)
#endif
			{
				// Calculate all cws
				for(j=0; j<8; j++)
				{
					PowervuCalculateCw(j,  seed[j], csaUsed, convolvedCw[j], cw[j], baseCw);
					
					if(csaUsed)
					{
						for(k = 0; k < 8; k += 4) {
							cw[j][k + 3] = ((cw[j][k] + cw[j][k + 1] + cw[j][k + 2]) & 0xff);
						}
					}
				}

#ifdef WITH_EMU				
				if(update_global_key)
				{
					for(j=0; j<EMU_STREAM_SERVER_MAX_CONNECTIONS; j++)
					{
						if(update_global_keys[j])
						{
							cw_item = (emu_stream_cw_item*)malloc(sizeof(emu_stream_cw_item));
							if(cw_item != NULL)
							{
								cw_item->csa_used = csaUsed;
								cw_item->is_even = ecm[0] == 0x80 ? 1 : 0;
								cs_ftime(&cw_item->write_time);
								add_ms_to_timeb(&cw_item->write_time, cfg.emu_stream_ecm_delay);
								memcpy(cw_item->cw, cw, sizeof(cw));
								ll_append(ll_emu_stream_delayed_keys[j], cw_item);
							}
						}
					}
				}
				
				if(cdata != NULL) 
				{
#endif
					for(j=0; j<8; j++)
					{
						if(csaUsed)
						{	
							if(cdata->pvu_csa_ks[j] == NULL)
								{  cdata->pvu_csa_ks[j] = get_key_struct(); }
								
							if(ecm[0] == 0x80)
								{ set_even_control_word(cdata->pvu_csa_ks[j], cw[j]); }
							else
								{ set_odd_control_word(cdata->pvu_csa_ks[j], cw[j]); }
							
							cdata->pvu_csa_used = 1;
						}
						else
						{					
							if(ecm[0] == 0x80)
								{ des_set_key(cw[j], cdata->pvu_des_ks[j][0]); }
							else
								{ des_set_key(cw[j], cdata->pvu_des_ks[j][1]); }
								
							cdata->pvu_csa_used = 0;
						}
					}
#ifdef WITH_EMU
				}
				
				if(cw_ex != NULL)
				{	
					cw_ex->mode = CW_MODE_MULTIPLE_CW;
					
					if(csaUsed)
					{
						cw_ex->algo = CW_ALGO_CSA;
						cw_ex->algo_mode = CW_ALGO_MODE_ECB;
					}
					else
					{
						cw_ex->algo = CW_ALGO_DES;
						cw_ex->algo_mode = CW_ALGO_MODE_ECB;
					}
					
					for(j=0; j<4; j++)
					{	
						dwp = cw_ex->audio[j];
						
						memset(dwp, 0, 16);
						
						if(ecm[0] == 0x80)
						{
							memcpy(dwp, cw[PVU_CW_A1+j], 8);
						
							if(csaUsed)
							{
								for(k = 0; k < 8; k += 4)
								{
									dwp[k + 3] = ((dwp[k] + dwp[k + 1] + dwp[k + 2]) & 0xff);
								}
							}
						}
						else
						{
							memcpy(&dwp[8], cw[PVU_CW_A1+j], 8);
							
							if(csaUsed)
							{
								for(k = 8; k < 16; k += 4)
								{
									dwp[k + 3] = ((dwp[k] + dwp[k + 1] + dwp[k + 2]) & 0xff);
								}
							}
						}
					}
					
					dwp = cw_ex->data;
					
					memset(dwp, 0, 16);
					
					if(ecm[0] == 0x80)
					{
						memcpy(dwp, cw[PVU_CW_HSD], 8);
					
						if(csaUsed)
						{
							for(k = 0; k < 8; k += 4)
							{
								dwp[k + 3] = ((dwp[k] + dwp[k + 1] + dwp[k + 2]) & 0xff);
							}
						}
					}
					else
					{
						memcpy(&dwp[8], cw[PVU_CW_HSD], 8);
						
						if(csaUsed)
						{
							for(k = 8; k < 16; k += 4)
							{
								dwp[k + 3] = ((dwp[k] + dwp[k + 1] + dwp[k + 2]) & 0xff);
							}
						}
					}
				}
#endif		
			}
			else
			{
				// Calculate only video cw
				PowervuCalculateCw(PVU_CW_VID, seed[PVU_CW_VID], csaUsed, convolvedCw[PVU_CW_VID], cw[PVU_CW_VID], baseCw);
			}
