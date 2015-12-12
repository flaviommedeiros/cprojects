switch (event) {
#ifdef CONFIG_IRDA_ULTRA
	case LM_UDATA_INDICATION:
		/* This is most bizzare. Those packets are  aka unreliable
		 * connected, aka IrLPT or SOCK_DGRAM/IRDAPROTO_UNITDATA.
		 * Why do we pass them as Ultra ??? Jean II */
		irlmp_connless_data_indication(self, skb);
		break;
#endif /* CONFIG_IRDA_ULTRA */
	case LM_CONNECT_REQUEST:
		IRDA_DEBUG(4, "%s(), LM_CONNECT_REQUEST\n", __func__);

		if (self->conn_skb) {
			IRDA_WARNING("%s: busy with another request!\n",
				     __func__);
			return -EBUSY;
		}
		/* Don't forget to refcount it (see irlmp_connect_request()) */
		skb_get(skb);
		self->conn_skb = skb;

		irlmp_next_lsap_state(self, LSAP_SETUP_PEND);

		/* Start watchdog timer (5 secs for now) */
		irlmp_start_watchdog_timer(self, 5*HZ);

		irlmp_do_lap_event(self->lap, LM_LAP_CONNECT_REQUEST, NULL);
		break;
	case LM_CONNECT_INDICATION:
		if (self->conn_skb) {
			IRDA_WARNING("%s: busy with another request!\n",
				     __func__);
			return -EBUSY;
		}
		/* Don't forget to refcount it (see irlap_driver_rcv()) */
		skb_get(skb);
		self->conn_skb = skb;

		irlmp_next_lsap_state(self, LSAP_CONNECT_PEND);

		/* Start watchdog timer
		 * This is not mentionned in the spec, but there is a rare
		 * race condition that can get the socket stuck.
		 * If we receive this event while our LAP is closing down,
		 * the LM_LAP_CONNECT_REQUEST get lost and we get stuck in
		 * CONNECT_PEND state forever.
		 * The other cause of getting stuck down there is if the
		 * higher layer never reply to the CONNECT_INDICATION.
		 * Anyway, it make sense to make sure that we always have
		 * a backup plan. 1 second is plenty (should be immediate).
		 * Jean II */
		irlmp_start_watchdog_timer(self, 1*HZ);

		irlmp_do_lap_event(self->lap, LM_LAP_CONNECT_REQUEST, NULL);
		break;
	default:
		IRDA_DEBUG(1, "%s(), Unknown event %s on LSAP %#02x\n",
			   __func__, irlmp_event[event], self->slsap_sel);
		break;
	}
