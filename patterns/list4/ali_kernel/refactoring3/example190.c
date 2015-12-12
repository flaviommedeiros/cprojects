switch (wValue >> 8) {

			case USB_DT_DEVICE:
				value = min(wLength, (u16) sizeof device_desc);
				memcpy(req->buf, &device_desc, value);
				break;
#ifdef CONFIG_USB_GADGET_DUALSPEED
			case USB_DT_DEVICE_QUALIFIER:
				if (!gadget->is_dualspeed)
					break;
				value = min(wLength,
						(u16) sizeof dev_qualifier);
				memcpy(req->buf, &dev_qualifier, value);
				break;

			case USB_DT_OTHER_SPEED_CONFIG:
				if (!gadget->is_dualspeed)
					break;
				/* FALLTHROUGH */
#endif /* CONFIG_USB_GADGET_DUALSPEED */
			case USB_DT_CONFIG:
				value = config_buf(gadget->speed, req->buf,
						wValue >> 8,
						wValue & 0xff,
						gadget->is_otg);
				if (value >= 0)
					value = min(wLength, (u16) value);
				break;

			case USB_DT_STRING:
				value = usb_gadget_get_string(&stringtab,
						wValue & 0xff, req->buf);
				if (value >= 0)
					value = min(wLength, (u16) value);
				break;
			}
