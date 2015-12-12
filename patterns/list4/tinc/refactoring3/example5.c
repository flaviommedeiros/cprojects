switch(device_type) {
		case DEVICE_TYPE_TUN:
			if(write(device_fd, packet->data + 14, packet->len - 14) < 0) {
				logger(LOG_ERR, "Error while writing to %s %s: %s", device_info,
					   device, strerror(errno));
				return false;
			}
			break;

		case DEVICE_TYPE_TUNIFHEAD: {
			u_int32_t type;
			struct iovec vector[2] = {{&type, sizeof(type)}, {packet->data + 14, packet->len - 14}};
			int af;
			
			af = (packet->data[12] << 8) + packet->data[13];

			switch (af) {
				case 0x0800:
					type = htonl(AF_INET);
					break;
				case 0x86DD:
					type = htonl(AF_INET6);
					break;
				default:
					ifdebug(TRAFFIC) logger(LOG_ERR,
							   "Unknown address family %x while writing packet to %s %s",
							   af, device_info, device);
					return false;
			}

			if(writev(device_fd, vector, 2) < 0) {
				logger(LOG_ERR, "Can't write to %s %s: %s", device_info, device,
					   strerror(errno));
				return false;
			}
			break;
		}
			
		case DEVICE_TYPE_TAP:
			if(write(device_fd, packet->data, packet->len) < 0) {
				logger(LOG_ERR, "Error while writing to %s %s: %s", device_info,
					   device, strerror(errno));
				return false;
			}
			break;

#ifdef ENABLE_TUNEMU
		case DEVICE_TYPE_TUNEMU:
			if(tunemu_write(device_fd, packet->data + 14, packet->len - 14) < 0) {
				logger(LOG_ERR, "Error while writing to %s %s: %s", device_info,
					   device, strerror(errno));
				return false;
			}
			break;
#endif

		default:
			return false;
	}
