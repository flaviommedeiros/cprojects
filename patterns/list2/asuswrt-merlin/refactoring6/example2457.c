if (!strcmp((char *)p_client_tab->device_name[p_client_tab->detail_info_num], db_device_name) &&
			    !strcmp((char *)p_client_tab->apple_model[p_client_tab->detail_info_num], db_apple_model) &&
			    p_client_tab->type[p_client_tab->detail_info_num] == atoi(db_type) &&
			    p_client_tab->http[p_client_tab->detail_info_num] == atoi(db_http) &&
			    p_client_tab->printer[p_client_tab->detail_info_num] == atoi(db_printer) &&
			    p_client_tab->itune[p_client_tab->detail_info_num] == atoi(db_itune) 
#ifdef RTCONFIG_BWDPI
                            && !strcmp(p_client_tab->bwdpi_host[p_client_tab->detail_info_num], db_bwdpi_host)
			    && !strcmp(p_client_tab->bwdpi_vendor[p_client_tab->detail_info_num], db_bwdpi_vendor)
			    && !strcmp(p_client_tab->bwdpi_type[p_client_tab->detail_info_num], db_bwdpi_type)
                            && !strcmp(p_client_tab->bwdpi_device[p_client_tab->detail_info_num], db_bwdpi_device)
#endif
			)
			{
NMP_DEBUG("DATA the same!\n");
				return;
			}
