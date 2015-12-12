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
