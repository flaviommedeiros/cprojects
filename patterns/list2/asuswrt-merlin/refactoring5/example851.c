#ifdef	CONFIG_USB_GADGET_DUALSPEED
if (dev->gadget->speed == USB_SPEED_HIGH)
					power = dev->hs_config->bMaxPower;
				else
#endif
					power = dev->config->bMaxPower;
