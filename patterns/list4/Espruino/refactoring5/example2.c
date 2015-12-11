#ifdef USE_USB_HID
if (handle->hidReportDescSize && req->wIndex == HID_INTERFACE_NUMBER)
    return USBD_HID_Setup(pdev, req);
  else
#endif
    return USBD_CDC_Setup(pdev, req);
