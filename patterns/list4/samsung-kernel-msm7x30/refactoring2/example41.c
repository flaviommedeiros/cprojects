#ifdef  WPA_SUPPLICANT_DRIVER_WEXT_SUPPORT
if (!pDevice->bWPASuppWextEnabled)
#endif
		bScheduleCommand((void *) pDevice,
				 WLAN_CMD_BSSID_SCAN,
				 pMgmt->abyDesireSSID);
