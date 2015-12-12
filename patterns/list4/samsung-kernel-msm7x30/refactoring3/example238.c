switch (data->dev->gadget->speed) {
	case USB_SPEED_LOW:
	case USB_SPEED_FULL:
		ep->desc = &data->desc;
		value = usb_ep_enable(ep);
		if (value == 0)
			data->state = STATE_EP_ENABLED;
		break;
#ifdef	CONFIG_USB_GADGET_DUALSPEED
	case USB_SPEED_HIGH:
		/* fails if caller didn't provide that descriptor... */
		ep->desc = &data->hs_desc;
		value = usb_ep_enable(ep);
		if (value == 0)
			data->state = STATE_EP_ENABLED;
		break;
#endif
	default:
		DBG(data->dev, "unconnected, %s init abandoned\n",
				data->name);
		value = -EINVAL;
	}
