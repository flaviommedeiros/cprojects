#ifdef WPS_NFC_DEVICE
if (strcmp(wps_ui_get_env("wps_sta_pin"), "NFC_PW") == 0) {
				env_pin = wps_nfc_dev_pw_str();
				oob_devpwid = wps_nfc_pw_id();
				pre_privkey = wps_nfc_priv_key();
			}
			else
#endif
			{
				env_pin = wps_get_conf("wps_device_pin");
			}
