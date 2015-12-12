switch(device_type) {
#ifdef ENABLE_TUNEMU
		case DEVICE_TYPE_TUNEMU: {
			char dynamic_name[256] = "";
        		device_fd = tunemu_open(dynamic_name);
		}
			break;
#endif
		default:
			device_fd = open(device, O_RDWR | O_NONBLOCK);
	}
