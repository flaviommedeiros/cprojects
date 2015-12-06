const uint8_t HID_DeviceDescriptor[HID_SIZ_DEVICE_DESC] =
  {
    0x12,   /*bLength */
    USB_DEVICE_DESCRIPTOR_TYPE,   /*bDescriptorType*/
    0x00,   /*bcdUSB */
    0x02,
    0x00,   /*bDeviceClass*/
    0x00,   /*bDeviceSubClass*/
    0x00,   /*bDeviceProtocol*/
    0x40,   /*bMaxPacketSize 64*/
    0x50,
    0x1D,   /* idVendor = 0x1D50 */
#if defined (SPARK_USB_MOUSE)
    0x7D,
    0x70,   /* idProduct = 0x707D (Temporary, need to request a new one from openmoko) */
#elif defined (SPARK_USB_KEYBOARD)
    0x7D,
    0x80,   /* idProduct = 0x807D (Temporary, need to request a new one from openmoko) */
#endif
    0x00,
    0x02,   /* bcdDevice = 2.00 */
    1,      /*Index of string descriptor describing manufacturer */
    2,      /*Index of string descriptor describing product*/
    3,      /*Index of string descriptor describing the device serial number */
    0x01    /*bNumConfigurations*/
  };
