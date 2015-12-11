__ALIGN_BEGIN uint8_t USBD_FS_DeviceDesc[USB_LEN_DEV_DESC] __ALIGN_END =
  {
    0x12,                       /*bLength */
    USB_DESC_TYPE_DEVICE,       /*bDescriptorType*/
#if (USBD_LPM_ENABLED == 1)
    0x01,                       /*bcdUSB */ /* changed to USB version 2.01 
                                               in order to support LPM L1 suspend
                                               resume test of USBCV3.0*/
#else  
    0x00,                       /* bcdUSB */
#endif  
    0x02,
    0x02,                       /*bDeviceClass - CDC */
    0x00,                       /*bDeviceSubClass*/
    0x00,                       /*bDeviceProtocol*/
    USB_MAX_EP0_SIZE,          /*bMaxPacketSize*/
    LOBYTE(USBD_VID),           /*idVendor*/
    HIBYTE(USBD_VID),           /*idVendor*/
    LOBYTE(USB_PRODUCT_ID),           /*idProduct*/
    HIBYTE(USB_PRODUCT_ID),           /*idProduct*/
    0x00,                       /*bcdDevice rel. 2.00*/
    0x02,
    USBD_IDX_MFC_STR,           /*Index of manufacturer  string*/
    USBD_IDX_PRODUCT_STR,       /*Index of product string*/
    USBD_IDX_SERIAL_STR,        /*Index of serial number string*/
    USBD_MAX_NUM_CONFIGURATION  /*bNumConfigurations*/
  } ;
