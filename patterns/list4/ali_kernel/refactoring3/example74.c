switch (chan) {
		case CHAN_NDIS_DATA:
			if (hynet_enable & (1 << card->myid)) {
                          /* give packet to network handler */
				hysdn_rx_netpkt(card, buf, len);
			}
			break;

		case CHAN_ERRLOG:
			hysdn_card_errlog(card, (tErrLogEntry *) buf, len);
			if (card->err_log_state == ERRLOG_STATE_ON)
				card->err_log_state = ERRLOG_STATE_START;	/* start new fetch */
			break;
#ifdef CONFIG_HYSDN_CAPI
         	case CHAN_CAPI:
/* give packet to CAPI handler */
			if (hycapi_enable & (1 << card->myid)) {
				hycapi_rx_capipkt(card, buf, len);
			}
			break;
#endif /* CONFIG_HYSDN_CAPI */
		default:
			printk(KERN_INFO "irq message channel %d len %d unhandled \n", chan, len);
			break;

	}
