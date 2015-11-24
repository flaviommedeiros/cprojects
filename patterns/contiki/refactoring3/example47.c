switch (usb_setup_buffer.bmRequestType) {
  case 0x80:                   /* standard device IN requests */
    switch (usb_setup_buffer.bRequest) {
    case GET_DESCRIPTOR:
      switch (HIGH_BYTE(usb_setup_buffer.wValue)) {
      case DEVICE:
        get_device_descriptor();
        break;
      case CONFIGURATION:
        get_configuration_descriptor();
        break;
      case STRING:
        get_string_descriptor();
        break;
      default:
        /* Unknown descriptor */
        return 0;
      }
      break;
    case GET_CONFIGURATION:
      get_configuration();
      break;
    case GET_STATUS:
      get_device_status();
      break;
    case GET_INTERFACE:
      get_interface();
      break;
    default:
      return 0;
    }
    break;
  case 0x81:                   /* standard interface IN requests */
    switch (usb_setup_buffer.bRequest) {
    case GET_STATUS:
      get_interface_status();
      break;
#ifdef HID_ENABLED
    case GET_DESCRIPTOR:
      switch (USB_setup_buffer.wValue.byte.high) {
      case REPORT:
        get_report_descriptor();
        break;
      }
      break;
#endif
    default:
      return 0;
    }
    break;
  case 0x82:                   /* standard endpoint IN requests */
    switch (usb_setup_buffer.bRequest) {
    case GET_STATUS:
      get_endpoint_status();
      break;
    default:
      return 0;
    }
    break;
  case 0x00:                   /* standard device OUT requests */
    switch (usb_setup_buffer.bRequest) {
    case SET_ADDRESS:
      PRINTF("Address: %d\n", LOW_BYTE(usb_setup_buffer.wValue));
      usb_flags |= USB_FLAG_ADDRESS_PENDING;
      /* The actual setting of the address is done when the status packet
         is sent. */
      usb_send_ctrl_status();
      break;
#if SETABLE_STRING_DESCRIPTORS > 0
    case SET_DESCRIPTOR:
      if(usb_setup_buffer.wValue.byte.high == STRING) {
        set_string_descriptor();
      } else {
        return 0;
      }
      break;
#endif
    case SET_CONFIGURATION:
      if(set_configuration()) {
#if 0
        config_msg.data.config = LOW_BYTE(usb_setup_buffer.wValue);
        notify_user(&config_msg);
#endif
      }
      break;
    default:
      return 0;
    }
    break;
  case 0x01:                   /* standard interface OUT requests */
    switch (usb_setup_buffer.bRequest) {
    case SET_INTERFACE:
      /* Change interface here if we support more than one */
      usb_send_ctrl_status();
      break;
    default:
      return 0;
    }
    break;
  case 0x02:                   /* standard endpoint OUT requests */
    switch (usb_setup_buffer.bRequest) {
    case SET_FEATURE:
    case CLEAR_FEATURE:
      if(usb_setup_buffer.wValue == ENDPOINT_HALT_FEATURE) {
        usb_arch_halt_endpoint(usb_setup_buffer.wIndex,
                               usb_setup_buffer.bRequest == SET_FEATURE);
        usb_send_ctrl_status();
      } else {
        usb_error_stall();
      }
      break;
    default:
      return 0;
    }
    break;
#ifdef HID_ENABLED
  case 0xa1:                   /* class specific interface IN request */
    switch (USB_setup_buffer.bRequest) {
    case GET_HID_REPORT:
      PRINTF("Get report\n");
      send_ctrl_response((code u_int8_t *) & zero_byte, sizeof(zero_byte));
      break;
    case GET_HID_IDLE:
      PRINTF("Get idle\n");
      send_ctrl_response((code u_int8_t *) & zero_byte, sizeof(zero_byte));
      break;
    default:
      return 0;
    }
    break;
  case 0x21:                   /* class specific interface OUT request */
    switch (USB_setup_buffer.bRequest) {
    case SET_HID_IDLE:
      PRINTF("Set idle\n");
      send_ctrl_status();
      break;
    default:
      return 0;
    }
    break;
#endif
  default:
    return 0;
  }
