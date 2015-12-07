#ifdef WPS_NFC_DEVICE
if (strcmp(env_pin, "NFC_PW") == 0) {
					env_pin = wps_nfc_dev_pw_str();
					oob_devpwid = wps_nfc_pw_id();
					pub_key_hash = wps_nfc_pub_key_hash();
				}
				else
#endif
				{
					if (wps_validate_pin(env_pin) == FALSE) {
						TUTRACE((TUTRACE_INFO, "Not a valid PIN [%s]\n",
							env_pin ? (char *)env_pin : ""));
						goto exit;
					}
				}
