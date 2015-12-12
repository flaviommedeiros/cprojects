switch (ax25->ax25_dev->values[AX25_VALUES_PROTOCOL]) {
		case AX25_PROTO_STD_SIMPLEX:
		case AX25_PROTO_STD_DUPLEX:
			ax25_send_iframe(ax25, skbn, (last) ? AX25_POLLON : AX25_POLLOFF);
			break;

#ifdef CONFIG_AX25_DAMA_SLAVE
		case AX25_PROTO_DAMA_SLAVE:
			ax25_send_iframe(ax25, skbn, AX25_POLLOFF);
			break;
#endif
		}
