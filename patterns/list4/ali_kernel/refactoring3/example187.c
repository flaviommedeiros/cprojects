switch (data->dev->gadget->speed) {
	case USB_SPEED_LOW:
	case USB_SPEED_FULL:
		value = usb_ep_enable (ep, &data->desc);
		if (value == 0)
			data->state = STATE_EP_ENABLED;
		break;
#ifdef	CONFIG_USB_GADGET_DUALSPEED
	case USB_SPEED_HIGH:
		/* fails if caller didn't provide that descriptor... */
		value = usb_ep_enable (ep, &data->hs_desc);
		if (value == 0)
			data->state = STATE_EP_ENABLED;
		break;
#endif
	default:
		DBG(data->dev, "unconnected, %s init abandoned\n",
				data->name);
		value = -EINVAL;
	}
