#ifdef HAVE_LIBUSB
if (devinfo->lowl == &lowl_usb)
		{
			if (lowl_usb_attach_kernel_driver(devinfo))
				bfg_need_detect_rescan = true;
		}
		else
#endif
			applog(LOG_WARNING, "Non-VCOM %s (%s) matched", devinfo->path, devinfo->devid);
