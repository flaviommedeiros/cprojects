if (
#if defined(RTCONFIG_USB_MODEM)
		    dualwan_unit__usbif(unit) ||
#endif
		    strcmp(wan_proto, "pppoe") == 0 ||
		    strcmp(wan_proto, "pptp") == 0 ||
		    strcmp(wan_proto, "l2tp") == 0) {
			fprintf(fp, "-A FORWARD -p tcp -m tcp --tcp-flags SYN,RST SYN -j TCPMSS --clamp-mss-to-pmtu\n");
			if (*macaccept)
				fprintf(fp, "-A %s -p tcp -m tcp --tcp-flags SYN,RST SYN -j TCPMSS --clamp-mss-to-pmtu\n", macaccept);
			break; // set one time
		}
