switch (msg) {

	case MSG_TDATA_IND:
		if (!(chan = capi_channel(dev, skb))) {
			printk(KERN_WARNING
			       "CAPI header: unknown channel id\n");
			break;
		}
		chan->r_refnum = skb->data[7];
		skb_pull(skb, 8);

		dev->dev_if->rcvcallb_skb(dev->id, chan->id, skb);

		if (capi_tdata_resp(chan, &skb2) > 0)
			pcbit_l2_write(dev, MSG_TDATA_RESP, refnum,
				       skb2, skb2->len);
		return;
		break;
	case MSG_TDATA_CONF:
		if (!(chan = capi_channel(dev, skb))) {
			printk(KERN_WARNING
			       "CAPI header: unknown channel id\n");
			break;
		}

#ifdef DEBUG
		if ((*((ushort *)(skb->data + 2))) != 0) {
			printk(KERN_DEBUG "TDATA_CONF error\n");
		}
#endif
#ifdef BLOCK_TIMER
		if (chan->queued == MAX_QUEUED) {
			del_timer(&chan->block_timer);
			chan->block_timer.function = NULL;
		}

#endif
		chan->queued--;

		ictl.driver = dev->id;
		ictl.command = ISDN_STAT_BSENT;
		ictl.arg = chan->id;
		dev->dev_if->statcallb(&ictl);
		break;

	case MSG_CONN_IND:
		/*
		 *  channel: 1st not used will do
		 *           if both are used we're in trouble
		 */

		if (!dev->b1->fsm_state)
			chan = dev->b1;
		else if (!dev->b2->fsm_state)
			chan = dev->b2;
		else {
			printk(KERN_INFO
			       "Incoming connection: no channels available");

			if ((len = capi_disc_req(*(ushort *)(skb->data), &skb2, CAUSE_NOCHAN)) > 0)
				pcbit_l2_write(dev, MSG_DISC_REQ, refnum, skb2, len);
			break;
		}

		cbdata.data.setup.CalledPN = NULL;
		cbdata.data.setup.CallingPN = NULL;

		capi_decode_conn_ind(chan, skb, &cbdata);
		cbdata.type = EV_NET_SETUP;

		pcbit_fsm_event(dev, chan, EV_NET_SETUP, NULL);

		if (pcbit_check_msn(dev, cbdata.data.setup.CallingPN))
			pcbit_fsm_event(dev, chan, EV_USR_PROCED_REQ, &cbdata);
		else
			pcbit_fsm_event(dev, chan, EV_USR_RELEASE_REQ, NULL);

		kfree(cbdata.data.setup.CalledPN);
		kfree(cbdata.data.setup.CallingPN);
		break;

	case MSG_CONN_CONF:
		/*
		 * We should be able to find the channel by the message
		 * reference number. The current version of the firmware
		 * doesn't sent the ref number correctly.
		 */
#ifdef DEBUG
		printk(KERN_DEBUG "refnum=%04x b1=%04x b2=%04x\n", refnum,
		       dev->b1->s_refnum,
		       dev->b2->s_refnum);
#endif
		/* We just try to find a channel in the right state */

		if (dev->b1->fsm_state == ST_CALL_INIT)
			chan = dev->b1;
		else {
			if (dev->b2->s_refnum == ST_CALL_INIT)
				chan = dev->b2;
			else {
				chan = NULL;
				printk(KERN_WARNING "Connection Confirm - no channel in Call Init state\n");
				break;
			}
		}
		if (capi_decode_conn_conf(chan, skb, &complete)) {
			printk(KERN_DEBUG "conn_conf indicates error\n");
			pcbit_fsm_event(dev, chan, EV_ERROR, NULL);
		}
		else
			if (complete)
				pcbit_fsm_event(dev, chan, EV_NET_CALL_PROC, NULL);
			else
				pcbit_fsm_event(dev, chan, EV_NET_SETUP_ACK, NULL);
		break;
	case MSG_CONN_ACTV_IND:

		if (!(chan = capi_channel(dev, skb))) {
			printk(KERN_WARNING
			       "CAPI header: unknown channel id\n");
			break;
		}

		if (capi_decode_conn_actv_ind(chan, skb)) {
			printk("error in capi_decode_conn_actv_ind\n");
			/* pcbit_fsm_event(dev, chan, EV_ERROR, NULL); */
			break;
		}
		chan->r_refnum = refnum;
		pcbit_fsm_event(dev, chan, EV_NET_CONN, NULL);
		break;
	case MSG_CONN_ACTV_CONF:

		if (!(chan = capi_channel(dev, skb))) {
			printk(KERN_WARNING
			       "CAPI header: unknown channel id\n");
			break;
		}

		if (capi_decode_conn_actv_conf(chan, skb) == 0)
			pcbit_fsm_event(dev, chan, EV_NET_CONN_ACK, NULL);

		else
			printk(KERN_DEBUG "decode_conn_actv_conf failed\n");
		break;

	case  MSG_SELP_CONF:

		if (!(chan = capi_channel(dev, skb))) {
			printk(KERN_WARNING
			       "CAPI header: unknown channel id\n");
			break;
		}

		if (!(err = capi_decode_sel_proto_conf(chan, skb)))
			pcbit_fsm_event(dev, chan, EV_NET_SELP_RESP, NULL);
		else {
			/* Error */
			printk("error %d - capi_decode_sel_proto_conf\n", err);
		}
		break;
	case MSG_ACT_TRANSP_CONF:
		if (!(chan = capi_channel(dev, skb))) {
			printk(KERN_WARNING
			       "CAPI header: unknown channel id\n");
			break;
		}

		if (!capi_decode_actv_trans_conf(chan, skb))
			pcbit_fsm_event(dev, chan, EV_NET_ACTV_RESP, NULL);
		break;

	case MSG_DISC_IND:

		if (!(chan = capi_channel(dev, skb))) {
			printk(KERN_WARNING
			       "CAPI header: unknown channel id\n");
			break;
		}

		if (!capi_decode_disc_ind(chan, skb))
			pcbit_fsm_event(dev, chan, EV_NET_DISC, NULL);
		else
			printk(KERN_WARNING "capi_decode_disc_ind - error\n");
		break;
	case MSG_DISC_CONF:
		if (!(chan = capi_channel(dev, skb))) {
			printk(KERN_WARNING
			       "CAPI header: unknown channel id\n");
			break;
		}

		if (!capi_decode_disc_ind(chan, skb))
			pcbit_fsm_event(dev, chan, EV_NET_RELEASE, NULL);
		else
			printk(KERN_WARNING "capi_decode_disc_conf - error\n");
		break;
	case MSG_INFO_IND:
#ifdef DEBUG
		printk(KERN_DEBUG "received Info Indication - discarded\n");
#endif
		break;
#ifdef DEBUG
	case MSG_DEBUG_188:
		capi_decode_debug_188(skb->data, skb->len);
		break;

	default:
		printk(KERN_DEBUG "pcbit_l3_receive: unknown message %08lx\n",
		       msg);
		break;
#endif
	}
