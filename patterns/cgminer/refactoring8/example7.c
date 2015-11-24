int _usb_transfer_read(struct cgpu_info *cgpu, uint8_t request_type, uint8_t bRequest, uint16_t wValue, uint16_t wIndex, char *buf, int bufsiz, int *amount, unsigned int timeout, __maybe_unused enum usb_cmds cmd)
{
	struct cg_usb_device *usbdev;
#if DO_USB_STATS
	struct timeval tv_start, tv_finish;
#endif
	unsigned char tbuf[64];
	int err, pstate;

	DEVWLOCK(cgpu, pstate);

	USBDEBUG("USB debug: _usb_transfer_read(%s (nodev=%s),type=%"PRIu8",req=%"PRIu8",value=%"PRIu16",index=%"PRIu16",bufsiz=%d,timeout=%u,cmd=%s)", cgpu->drv->name, bool_str(cgpu->usbinfo.nodev), request_type, bRequest, wValue, wIndex, bufsiz, timeout, usb_cmdname(cmd));

	if (cgpu->usbinfo.nodev) {
		USB_REJECT(cgpu, MODE_CTRL_READ);

		err = LIBUSB_ERROR_NO_DEVICE;
		goto out_noerrmsg;
	}
	usbdev = cgpu->usbdev;
	if (timeout == DEVTIMEOUT)
		timeout = usbdev->found->timeout;

	*amount = 0;

	memset(tbuf, 0, 64);
	STATS_TIMEVAL(&tv_start);
	err = usb_control_transfer(cgpu, usbdev->handle, request_type, bRequest,
				   wValue, wIndex, tbuf, (uint16_t)bufsiz, timeout);
	STATS_TIMEVAL(&tv_finish);
	USB_STATS(cgpu, &tv_start, &tv_finish, err, MODE_CTRL_READ, cmd, SEQ0, timeout);
	cg_memcpy(buf, tbuf, bufsiz);

	USBDEBUG("USB debug: @_usb_transfer_read(%s (nodev=%s)) amt/err=%d%s%s%s", cgpu->drv->name, bool_str(cgpu->usbinfo.nodev), err, isnodev(err), err > 0 ? " = " : BLANK, err > 0 ? bin2hex((unsigned char *)buf, (size_t)err) : BLANK);

	if (err > 0) {
		*amount = err;
		err = 0;
	}
	if (err < 0 && err != LIBUSB_ERROR_TIMEOUT) {
		applog(LOG_WARNING, "%s %i usb transfer read err:(%d) %s", cgpu->drv->name, cgpu->device_id,
		       err, libusb_error_name(err));
	}
out_noerrmsg:
	if (NOCONTROLDEV(err))
		release_cgpu(cgpu);

	DEVWUNLOCK(cgpu, pstate);

	return err;
}
