if(
#ifdef RTCONFIG_USB_PRINTER
			!got_printer
#else
			1
#endif
			&&
#ifdef RTCONFIG_USB_MODEM
			!got_modem
#else
			1
#endif
			&& !got_disk
			)
		return NULL;
