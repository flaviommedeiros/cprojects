switch(device_type) {
		case DEVICE_TYPE_TUN:
#ifdef ENABLE_TUNEMU
		case DEVICE_TYPE_TUNEMU:
			if(device_type == DEVICE_TYPE_TUNEMU)
				lenin = tunemu_read(device_fd, packet->data + 14, MTU - 14);
			else
#endif
				lenin = read(device_fd, packet->data + 14, MTU - 14);

			if(lenin <= 0) {
				logger(LOG_ERR, "Error while reading from %s %s: %s", device_info,
					   device, strerror(errno));
				return false;
			}

			switch(packet->data[14] >> 4) {
				case 4:
					packet->data[12] = 0x08;
					packet->data[13] = 0x00;
					break;
				case 6:
					packet->data[12] = 0x86;
					packet->data[13] = 0xDD;
					break;
				default:
					ifdebug(TRAFFIC) logger(LOG_ERR,
							   "Unknown IP version %d while reading packet from %s %s",
							   packet->data[14] >> 4, device_info, device);
					return false;
			}

			memset(packet->data, 0, 12);
			packet->len = lenin + 14;
			break;

		case DEVICE_TYPE_TUNIFHEAD: {
			u_int32_t type;
			struct iovec vector[2] = {{&type, sizeof(type)}, {packet->data + 14, MTU - 14}};

			if((lenin = readv(device_fd, vector, 2)) <= 0) {
				logger(LOG_ERR, "Error while reading from %s %s: %s", device_info,
					   device, strerror(errno));
				return false;
			}

			switch (ntohl(type)) {
				case AF_INET:
					packet->data[12] = 0x08;
					packet->data[13] = 0x00;
					break;

				case AF_INET6:
					packet->data[12] = 0x86;
					packet->data[13] = 0xDD;
					break;

				default:
					ifdebug(TRAFFIC) logger(LOG_ERR,
							   "Unknown address family %x while reading packet from %s %s",
							   ntohl(type), device_info, device);
					return false;
			}

			memset(packet->data, 0, 12);
			packet->len = lenin + 10;
			break;
		}

		case DEVICE_TYPE_TAP:
			if((lenin = read(device_fd, packet->data, MTU)) <= 0) {
				logger(LOG_ERR, "Error while reading from %s %s: %s", device_info,
					   device, strerror(errno));
				return false;
			}

			packet->len = lenin;
			break;

		default:
			return false;
	}
