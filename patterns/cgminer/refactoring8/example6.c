int __usb_transfer(struct cgpu_info *cgpu, uint8_t request_type, uint8_t bRequest, uint16_t wValue, uint16_t wIndex, uint32_t *data, int siz, unsigned int timeout, __maybe_unused enum usb_cmds cmd)
{
	struct cg_usb_device *usbdev;
#if DO_USB_STATS
	struct timeval tv_start, tv_finish;
#endif
	unsigned char buf[64];
	uint32_t *buf32 = (uint32_t *)buf;
	int err, i, bufsiz;

	USBDEBUG("USB debug: _usb_transfer(%s (nodev=%s),type=%"PRIu8",req=%"PRIu8",value=%"PRIu16",index=%"PRIu16",siz=%d,timeout=%u,cmd=%s)", cgpu->drv->name, bool_str(cgpu->usbinfo.nodev), request_type, bRequest, wValue, wIndex, siz, timeout, usb_cmdname(cmd));

	if (cgpu->usbinfo.nodev) {
		USB_REJECT(cgpu, MODE_CTRL_WRITE);

		err = LIBUSB_ERROR_NO_DEVICE;
		goto out_;
	}
	usbdev = cgpu->usbdev;
	if (timeout == DEVTIMEOUT)
		timeout = usbdev->found->timeout;

	USBDEBUG("USB debug: @_usb_transfer() data=%s", bin2hex((unsigned char *)data, (size_t)siz));

	if (siz > 0) {
		bufsiz = siz - 1;
		bufsiz >>= 2;
		bufsiz++;
		for (i = 0; i < bufsiz; i++)
			buf32[i] = htole32(data[i]);
	}

	USBDEBUG("USB debug: @_usb_transfer() buf=%s", bin2hex(buf, (size_t)siz));

	STATS_TIMEVAL(&tv_start);
	err = usb_control_transfer(cgpu, usbdev->handle, request_type, bRequest,
				   wValue, wIndex, buf, (uint16_t)siz, timeout);
	STATS_TIMEVAL(&tv_finish);
	USB_STATS(cgpu, &tv_start, &tv_finish, err, MODE_CTRL_WRITE, cmd, SEQ0, timeout);

	USBDEBUG("USB debug: @_usb_transfer(%s (nodev=%s)) err=%d%s", cgpu->drv->name, bool_str(cgpu->usbinfo.nodev), err, isnodev(err));

	if (err < 0 && err != LIBUSB_ERROR_TIMEOUT) {
		applog(LOG_WARNING, "%s %i usb transfer err:(%d) %s", cgpu->drv->name, cgpu->device_id,
		       err, libusb_error_name(err));
	}
out_:
	return err;
}
