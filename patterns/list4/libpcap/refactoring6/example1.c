if (!device || strcmp(device, "any") == 0
#ifdef HAVE_DAG_API
	    || strstr(device, "dag") != NULL
#endif
#ifdef HAVE_SEPTEL_API
	    || strstr(device, "septel") != NULL
#endif
#ifdef PCAP_SUPPORT_BT
	    || strstr(device, "bluetooth") != NULL
#endif
#ifdef PCAP_SUPPORT_USB
	    || strstr(device, "usbmon") != NULL
#endif
#ifdef HAVE_SNF_API
	    || strstr(device, "snf") != NULL
#endif
	    ) {
		*netp = *maskp = 0;
		return 0;
	}
