switch (ax25->ax25_dev->values[AX25_VALUES_PROTOCOL]) {
	case AX25_PROTO_STD_SIMPLEX:
	case AX25_PROTO_STD_DUPLEX:
		queued = ax25_std_frame_in(ax25, skb, type);
		break;

#ifdef CONFIG_AX25_DAMA_SLAVE
	case AX25_PROTO_DAMA_SLAVE:
		if (dama || ax25->ax25_dev->dama.slave)
			queued = ax25_ds_frame_in(ax25, skb, type);
		else
			queued = ax25_std_frame_in(ax25, skb, type);
		break;
#endif
	}
