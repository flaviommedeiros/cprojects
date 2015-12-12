#ifdef COMMON_MEMORY
if(!usb_hcd_check_unlink_urb(&hcd->usb_hcd, urb,0))
					usb_hcd_unlink_urb_from_ep(&hcd->usb_hcd,
						urb);
