switch (usb_get_dr_mode(&pdev->dev)) {
#if defined CONFIG_USB_MUSB_DUAL_ROLE || defined CONFIG_USB_MUSB_HOST
	case USB_DR_MODE_HOST:
		pdata.mode = MUSB_PORT_MODE_HOST;
		break;
#endif
#ifdef CONFIG_USB_MUSB_DUAL_ROLE
	case USB_DR_MODE_OTG:
		glue->extcon = extcon_get_edev_by_phandle(&pdev->dev, 0);
		if (IS_ERR(glue->extcon)) {
			if (PTR_ERR(glue->extcon) == -EPROBE_DEFER)
				return -EPROBE_DEFER;
			dev_err(&pdev->dev, "Invalid or missing extcon\n");
			return PTR_ERR(glue->extcon);
		}
		pdata.mode = MUSB_PORT_MODE_DUAL_ROLE;
		break;
#endif
	default:
		dev_err(&pdev->dev, "Invalid or missing 'dr_mode' property\n");
		return -EINVAL;
	}
