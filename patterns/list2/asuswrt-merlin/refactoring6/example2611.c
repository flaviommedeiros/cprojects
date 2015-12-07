if(!strcmp(name, "wl_unit")
					|| !strcmp(name, "wan_unit")
					|| !strcmp(name, "lan_unit")
#ifdef RTCONFIG_DSL
					|| !strcmp(name, "dsl_unit")
#endif
#ifdef RTCONFIG_OPENVPN
					|| !strcmp(name, "vpn_server_unit")
					|| !strcmp(name, "vpn_client_unit")
#endif
					) {
				unit = atoi(value);
				if(unit != nvram_get_int(name)) {
					nvram_set_int(name, unit);
					nvram_modified=1;
				}
			}
			else if(!strcmp(name, "wl_subunit")) {
				subunit = atoi(value);
				if(subunit!=nvram_get_int(name)) {
					nvram_set_int(name, subunit);
					nvram_modified=1;
				}
			}
			else if(!strncmp(name, "wl_", 3) && unit != -1) {
				// convert wl_ to wl[unit], only when wl_unit is parsed
				if(subunit==-1||subunit==0)
					snprintf(prefix, sizeof(prefix), "wl%d_", unit);
				else snprintf(prefix, sizeof(prefix), "wl%d.%d_", unit, subunit);
				(void)strcat_r(prefix, name+3, tmp);
				if(strcmp(nvram_safe_get(tmp), value))
				{
					nvram_set(tmp, value);
					nvram_modified = 1;
					nvram_modified_wl = 1;
					_dprintf("set %s=%s\n", tmp, value);

#ifdef RTCONFIG_QTN
					if (unit == 1)
					{
						if (rpc_qtn_ready())
						{
							rpc_parse_nvram(tmp, value);
						}
					}
#endif
				}
			}
			else if(!strncmp(name, "wan_", 4) && unit != -1) {
				snprintf(prefix, sizeof(prefix), "wan%d_", unit);
				(void)strcat_r(prefix, name+4, tmp);

				if(strcmp(nvram_safe_get(tmp), value)) {
					nvram_set(tmp, value);
					nvram_modified = 1;
					_dprintf("set %s=%s\n", tmp, value);
				}					
			}
			else if(!strncmp(name, "lan_", 4) && unit != -1) {
				snprintf(prefix, sizeof(prefix), "lan%d_", unit);
				(void)strcat_r(prefix, name+4, tmp);

				if(strcmp(nvram_safe_get(tmp), value)) {
					nvram_set(tmp, value);
					nvram_modified = 1;
					_dprintf("set %s=%s\n", tmp, value);
				}
			}
#ifdef RTCONFIG_DSL
			else if(!strcmp(name, "dsl_subunit")) {
				subunit = atoi(value);
				if(subunit!=nvram_get_int(name)) {
					nvram_set_int(name, subunit);
					nvram_modified=1;
				}
			}
			else if(!strncmp(name, "dsl_", 4) && unit != -1) {
				if(subunit==-1||subunit==0)
					snprintf(prefix, sizeof(prefix), "dsl%d_", unit);
				else
					snprintf(prefix, sizeof(prefix), "dsl%d.%d_", unit, subunit);
				(void)strcat_r(prefix, name+4, tmp);

				if(strcmp(nvram_safe_get(tmp), value)) {
					nvram_set(tmp, value);
					nvram_modified = 1;
					_dprintf("set %s=%s\n", tmp, value);
				}
			}
#endif
#ifdef RTCONFIG_OPENVPN
			else if(!strncmp(name, "vpn_server_", 11) && unit!=-1) {
				snprintf(prefix, sizeof(prefix), "vpn_server%d_", unit);
				(void)strcat_r(prefix, name+11, tmp);

				if(strcmp(nvram_safe_get(tmp), value)) {
					nvram_set(tmp, value);
					nvram_modified = 1;
					_dprintf("set %s=%s\n", tmp, value);
				}
			}
			else if(!strncmp(name, "vpn_client_", 11) && unit!=-1) {
				snprintf(prefix, sizeof(prefix), "vpn_client%d_", unit);
				(void)strcat_r(prefix, name+11, tmp);

				if(strcmp(nvram_safe_get(tmp), value)) {
					nvram_set(tmp, value);
					nvram_modified = 1;
					_dprintf("set %s=%s\n", tmp, value);
				}
			}
			else if(!strncmp(name, "vpn_crt", 7)) {
				nvram_set(name, value);			// save to nvram
				get_parsed_crt(name, tmp, sizeof (tmp));// then migrate to jffs
				_dprintf("set %s=%s'n", name, value);
			}
#endif
			else if(!strncmp(name, "sshd_", 5)) {
				write_encoded_crt(name, value);
				nvram_modified = 1;
				_dprintf("set %s=%s\n", name, value);
			}
#ifdef RTCONFIG_DISK_MONITOR
			else if(!strncmp(name, "diskmon_", 8)) {
				snprintf(prefix, sizeof(prefix), "usb_path%s_diskmon_", nvram_safe_get("diskmon_usbport"));
				(void)strcat_r(prefix, name+8, tmp);

				if(strcmp(nvram_safe_get(tmp), value)) {
					nvram_set(tmp, value);
					nvram_modified = 1;
					_dprintf("set %s=%s\n", tmp, value);
				}
			}
#endif
#ifdef RTCONFIG_JFFS2USERICON
			else if(!strcmp(name, "custom_usericon")) {
				(void)handle_upload_icon(value);
				nvram_set(name, "");
				nvram_modified = 1;
			}
			else if(!strcmp(name, "custom_usericon_del")) {
				(void)del_upload_icon(value);
				nvram_set(name, "");
				nvram_modified = 1;
			}
#endif
			// TODO: add other multiple instance handle here
			else if(strcmp(nvram_safe_get(name), value)) {

				// the flag is set only when username or password is changed
				if(!strcmp(t->name, "http_username")
						|| !strcmp(t->name, "http_passwd")){
#ifdef RTCONFIG_USB
					if(!strcmp(t->name, "http_username")){
						strncpy(orig_acc, nvram_safe_get(name), 128);
						strncpy(modified_acc, value, 128);
					}
					else if(!strcmp(t->name, "http_passwd"))
						strncpy(modified_pass, value, 128);

#endif

					acc_modified = 1;
					change_passwd = 1;
				}

#ifdef RTCONFIG_HTTPS
				if(!strcmp(name, "PM_SMTP_AUTH_PASS")){
					_dprintf("PM_SMTP_AUTH_PASS match\n");
					char pw_tmp[256];
					memset(pw_tmp, 0, 256);
					strncpy(pw_tmp, value,256);
					strncpy(value, (char *) pwenc(pw_tmp),256);
				}
#endif

#ifdef RTCONFIG_DUALWAN//Cherry Cho added for exchanging settings of dualwan in 2014/10/20.
				if(!strcmp(name, "wans_dualwan")){
					save_index_to_interface();
					save_interface_to_index(value);
				}
#endif

#if defined(RTCONFIG_JFFS2) || defined(RTCONFIG_BRCM_NAND_JFFS2) || defined(RTCONFIG_UBIFS)
				if(!strcmp(name, "modem_bytes_data_cycle") || !strcmp(name, "modem_bytes_data_limit") || !strcmp(name, "modem_bytes_data_warning")){
					notify_rc("restart_set_dataset");
				}
#endif				

				nvram_set(name, value);
				nvram_modified = 1;
				_dprintf("set %s=%s\n", name, value);

#if defined(RTCONFIG_USB_MODEM) && (defined(RTCONFIG_JFFS2) || defined(RTCONFIG_BRCM_NAND_JFFS2) || defined(RTCONFIG_UBIFS))
				if(!strncmp(name, "modem_bytes_data", 16)){
					got_modem_data = 1;
				}
#endif
			}
