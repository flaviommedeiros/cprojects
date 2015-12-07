#ifdef RTCONFIG_USB_PRINTER
if(!strcmp(been_type, "printer")){ // Top priority
				return 0;
			}
			else
#endif
#ifdef RTCONFIG_USB_MODEM
			if(!strcmp(been_type, "modem")){ // 2nd priority
#ifdef RTCONFIG_USB_PRINTER
				if(strcmp(known_type, "printer"))
#endif
					return 0;
			}
			else
#endif
			if(!strcmp(been_type, "storage")){
#if defined(RTCONFIG_USB_PRINTER) || defined(RTCONFIG_USB_MODEM)
				if(
#ifdef RTCONFIG_USB_PRINTER
						strcmp(known_type, "printer")
#else
						1
#endif
					 	&&
#ifdef RTCONFIG_USB_MODEM
						strcmp(known_type, "modem")
#else
						1
#endif
						)
#endif
					return 0;
			}
			else
			{ // unknown device.
				return 0;
			}
