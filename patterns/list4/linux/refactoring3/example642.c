switch (event) {
	case CONNECT_REQUEST:
		IRDA_ASSERT(self->netdev != NULL, return -1;);

		if (self->media_busy) {
			/* Note : this will never happen, because we test
			 * media busy in irlap_connect_request() and
			 * postpone the event... - Jean II */
			pr_debug("%s(), CONNECT_REQUEST: media busy!\n",
				 __func__);

			/* Always switch state before calling upper layers */
			irlap_next_state(self, LAP_NDM);

			irlap_disconnect_indication(self, LAP_MEDIA_BUSY);
		} else {
			irlap_send_snrm_frame(self, &self->qos_rx);

			/* Start Final-bit timer */
			irlap_start_final_timer(self, self->final_timeout);

			self->retry_count = 0;
			irlap_next_state(self, LAP_SETUP);
		}
		break;
	case RECV_SNRM_CMD:
		/* Check if the frame contains and I field */
		if (info) {
			self->daddr = info->daddr;
			self->caddr = info->caddr;

			irlap_next_state(self, LAP_CONN);

			irlap_connect_indication(self, skb);
		} else {
			pr_debug("%s(), SNRM frame does not contain an I field!\n",
				 __func__);
		}
		break;
	case DISCOVERY_REQUEST:
		IRDA_ASSERT(info != NULL, return -1;);

		if (self->media_busy) {
			pr_debug("%s(), DISCOVERY_REQUEST: media busy!\n",
				 __func__);
			/* irlap->log.condition = MEDIA_BUSY; */

			/* This will make IrLMP try again */
			irlap_discovery_confirm(self, NULL);
			/* Note : the discovery log is not cleaned up here,
			 * it will be done in irlap_discovery_request()
			 * Jean II */
			return 0;
		}

		self->S = info->S;
		self->s = info->s;
		irlap_send_discovery_xid_frame(self, info->S, info->s, TRUE,
					       info->discovery);
		self->frame_sent = FALSE;
		self->s++;

		irlap_start_slot_timer(self, self->slot_timeout);
		irlap_next_state(self, LAP_QUERY);
		break;
	case RECV_DISCOVERY_XID_CMD:
		IRDA_ASSERT(info != NULL, return -1;);

		/* Assert that this is not the final slot */
		if (info->s <= info->S) {
			self->slot = irlap_generate_rand_time_slot(info->S,
								   info->s);
			if (self->slot == info->s) {
				discovery_rsp = irlmp_get_discovery_response();
				discovery_rsp->data.daddr = info->daddr;

				irlap_send_discovery_xid_frame(self, info->S,
							       self->slot,
							       FALSE,
							       discovery_rsp);
				self->frame_sent = TRUE;
			} else
				self->frame_sent = FALSE;

			/*
			 * Go to reply state until end of discovery to
			 * inhibit our own transmissions. Set the timer
			 * to not stay forever there... Jean II
			 */
			irlap_start_query_timer(self, info->S, info->s);
			irlap_next_state(self, LAP_REPLY);
		} else {
		/* This is the final slot. How is it possible ?
		 * This would happen is both discoveries are just slightly
		 * offset (if they are in sync, all packets are lost).
		 * Most often, all the discovery requests will be received
		 * in QUERY state (see my comment there), except for the
		 * last frame that will come here.
		 * The big trouble when it happen is that active discovery
		 * doesn't happen, because nobody answer the discoveries
		 * frame of the other guy, so the log shows up empty.
		 * What should we do ?
		 * Not much. It's too late to answer those discovery frames,
		 * so we just pass the info to IrLMP who will put it in the
		 * log (and post an event).
		 * Another cause would be devices that do discovery much
		 * slower than us, however the latest fixes should minimise
		 * those cases...
		 * Jean II
		 */
			pr_debug("%s(), Receiving final discovery request, missed the discovery slots :-(\n",
				 __func__);

			/* Last discovery request -> in the log */
			irlap_discovery_indication(self, info->discovery);
		}
		break;
	case MEDIA_BUSY_TIMER_EXPIRED:
		/* A bunch of events may be postponed because the media is
		 * busy (usually immediately after we close a connection),
		 * or while we are doing discovery (state query/reply).
		 * In all those cases, the media busy flag will be cleared
		 * when it's OK for us to process those postponed events.
		 * This event is not mentioned in the state machines in the
		 * IrLAP spec. It's because they didn't consider Ultra and
		 * postponing connection request is optional.
		 * Jean II */
#ifdef CONFIG_IRDA_ULTRA
		/* Send any pending Ultra frames if any */
		if (!skb_queue_empty(&self->txq_ultra)) {
			/* We don't send the frame, just post an event.
			 * Also, previously this code was in timer.c...
			 * Jean II */
			ret = (*state[self->state])(self, SEND_UI_FRAME,
						    NULL, NULL);
		}
#endif /* CONFIG_IRDA_ULTRA */
		/* Check if we should try to connect.
		 * This code was previously in irlap_do_event() */
		if (self->connect_pending) {
			self->connect_pending = FALSE;

			/* This one *should* not pend in this state, except
			 * if a socket try to connect and immediately
			 * disconnect. - clear - Jean II */
			if (self->disconnect_pending)
				irlap_disconnect_indication(self, LAP_DISC_INDICATION);
			else
				ret = (*state[self->state])(self,
							    CONNECT_REQUEST,
							    NULL, NULL);
			self->disconnect_pending = FALSE;
		}
		/* Note : one way to test if this code works well (including
		 * media busy and small busy) is to create a user space
		 * application generating an Ultra packet every 3.05 sec (or
		 * 2.95 sec) and to see how it interact with discovery.
		 * It's fairly easy to check that no packet is lost, that the
		 * packets are postponed during discovery and that after
		 * discovery indication you have a 100ms "gap".
		 * As connection request and Ultra are now processed the same
		 * way, this avoid the tedious job of trying IrLAP connection
		 * in all those cases...
		 * Jean II */
		break;
#ifdef CONFIG_IRDA_ULTRA
	case SEND_UI_FRAME:
	{
		int i;
		/* Only allowed to repeat an operation twice */
		for (i=0; ((i<2) && (self->media_busy == FALSE)); i++) {
			skb = skb_dequeue(&self->txq_ultra);
			if (skb)
				irlap_send_ui_frame(self, skb, CBROADCAST,
						    CMD_FRAME);
			else
				break;
			/* irlap_send_ui_frame() won't increase skb reference
			 * count, so no dev_kfree_skb() - Jean II */
		}
		if (i == 2) {
			/* Force us to listen 500 ms again */
			irda_device_set_media_busy(self->netdev, TRUE);
		}
		break;
	}
	case RECV_UI_FRAME:
		/* Only accept broadcast frames in NDM mode */
		if (info->caddr != CBROADCAST) {
			pr_debug("%s(), not a broadcast frame!\n",
				 __func__);
		} else
			irlap_unitdata_indication(self, skb);
		break;
#endif /* CONFIG_IRDA_ULTRA */
	case RECV_TEST_CMD:
		/* Remove test frame header */
		skb_pull(skb, sizeof(struct test_frame));

		/*
		 * Send response. This skb will not be sent out again, and
		 * will only be used to send out the same info as the cmd
		 */
		irlap_send_test_frame(self, CBROADCAST, info->daddr, skb);
		break;
	case RECV_TEST_RSP:
		pr_debug("%s() not implemented!\n", __func__);
		break;
	default:
		pr_debug("%s(), Unknown event %s\n", __func__,
			 irlap_event[event]);

		ret = -1;
		break;
	}
