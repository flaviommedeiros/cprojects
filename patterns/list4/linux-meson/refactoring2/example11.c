#ifdef CONFIG_USB_DWC_OTG_LPM
if (wValue != UHF_PORT_L1)
#endif
			if (!wIndex || wIndex > 1)
				goto error;
