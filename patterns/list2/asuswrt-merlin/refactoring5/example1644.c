#ifdef RTCONFIG_USB_PRINTER
if(got_printer > 0) // Top priority
		strcpy(buf, "printer");
	else
#endif
#ifdef RTCONFIG_USB_MODEM
	if(got_modem > 0) // 2nd priority
		strcpy(buf, "modem");
	else
#endif
	if(got_disk > 0)
		strcpy(buf, "storage");
	else
		return NULL;
