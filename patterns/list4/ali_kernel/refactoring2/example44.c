#ifdef WPA_SUPPLICANT_DRIVER_WEXT_SUPPORT
if(pDevice->bWPASuppWextEnabled !=TRUE)
	 #endif
           bScheduleCommand((HANDLE) pDevice, WLAN_CMD_BSSID_SCAN, pMgmt->abyDesireSSID);
