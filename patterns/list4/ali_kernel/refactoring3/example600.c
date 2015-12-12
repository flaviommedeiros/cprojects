switch (protocol) {
#ifdef CONFIG_IRDA_ULTRA
		case IRDAPROTO_ULTRA:
			sock->ops = &irda_ultra_ops;
			/* Initialise now, because we may send on unbound
			 * sockets. Jean II */
			self->max_data_size = ULTRA_MAX_DATA - LMP_PID_HEADER;
			self->max_header_size = IRDA_MAX_HEADER + LMP_PID_HEADER;
			break;
#endif /* CONFIG_IRDA_ULTRA */
		case IRDAPROTO_UNITDATA:
			sock->ops = &irda_dgram_ops;
			/* We let Unitdata conn. be like seqpack conn. */
			self->max_sdu_size_rx = TTP_SAR_UNBOUND;
			break;
		default:
			sk_free(sk);
			return -ESOCKTNOSUPPORT;
		}
