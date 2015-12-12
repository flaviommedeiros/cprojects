if (!driver || 
#if LINUX_VERSION_CODE  > KERNEL_VERSION(3,6,0)
	    !driver->bind ||
#else
		!bind ||driver->speed == USB_SPEED_UNKNOWN ||
#endif
	    !driver->unbind || !driver->disconnect || !driver->setup) {
		DWC_ERROR("usb_gadget_register_driver EINVAL\n");
		return -EINVAL;
	}
