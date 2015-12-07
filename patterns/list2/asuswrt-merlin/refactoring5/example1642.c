#ifdef RTCONFIG_USB_PRINTER
if(isPrinterInterface(interface_name))
			++got_printer;
		else
#endif
#ifdef RTCONFIG_USB_MODEM
		if(isSerialInterface(interface_name, 0, 0, 0) || isACMInterface(interface_name, 0, 0, 0))
			++got_modem;
		else
#endif
		if(isStorageInterface(interface_name))
			++got_disk;
		else
			++got_others;
