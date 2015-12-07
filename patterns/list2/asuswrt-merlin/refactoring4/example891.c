#ifdef	CONFIG_USB_DEVICEFS
if (add_uevent_var(env, "DEVICE=/proc/bus/usb/%03d/%03d",
			   usb_dev->bus->busnum, usb_dev->devnum))
		return -ENOMEM;
