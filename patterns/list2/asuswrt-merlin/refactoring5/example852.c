#ifdef	CONFIG_USB_GADGET_DUALSPEED
if (gadget->speed == USB_SPEED_HIGH) {
				config = dev->hs_config->bConfigurationValue;
				power = dev->hs_config->bMaxPower;
			} else
#endif
			{
				config = dev->config->bConfigurationValue;
				power = dev->config->bMaxPower;
			}
