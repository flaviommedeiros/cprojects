switch(device_type) {
#ifdef ENABLE_TUNEMU
		case DEVICE_TYPE_TUNEMU:
			tunemu_close(device_fd);
			break;
#endif
		default:
			close(device_fd);
	}
