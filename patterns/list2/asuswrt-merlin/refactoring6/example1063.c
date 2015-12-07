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
