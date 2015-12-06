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
