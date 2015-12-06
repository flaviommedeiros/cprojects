switch (descriptor_type)
	{
	case DEVICE_DESCRIPTOR:
	  data_to_transfer = Usb_get_dev_desc_length(); //!< sizeof (usb_user_device_descriptor);
	  pbuffer          = Usb_get_dev_desc_pointer();
	  break;
	case CONFIGURATION_DESCRIPTOR:
		data_to_transfer = Usb_get_conf_desc_length(string_type); //!< sizeof (usb_user_configuration_descriptor);
		pbuffer          = Usb_get_conf_desc_pointer(string_type);
	  break;
#if 1 
	case STRING_DESCRIPTOR:
	  if(string_type!=LANG_ID) {
		usb_get_string_descriptor(string_type);
		return;
	  }
#endif
	default:
		dummy = Usb_read_byte();
		dummy = Usb_read_byte();
        if (dummy) {;}  
		LSBwLength = Usb_read_byte();
		MSBwLength = Usb_read_byte();
		byteswereread=1;
		if( usb_user_get_descriptor(descriptor_type, string_type)==FALSE ) {
		    Usb_enable_stall_handshake(); //TODO:is this necessary, Win7 flaky without?
			Usb_ack_receive_setup();
			return;
		}
	  break;
	}
