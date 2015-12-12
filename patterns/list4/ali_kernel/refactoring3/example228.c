switch (message[0]) {
    case ABORT:
    case ABORT_TAG:
    case COMMAND_COMPLETE:
	if (host->scsi.phase != PHASE_STATUSIN) {
	    printk(KERN_ERR "scsi%d.%c: command complete following non-status in phase?\n",
		    host->host->host_no, acornscsi_target(host));
	    acornscsi_dumplog(host, host->SCpnt->device->id);
	}
	host->scsi.phase = PHASE_DONE;
	host->scsi.SCp.Message = message[0];
	break;

    case SAVE_POINTERS:
	/*
	 * ANSI standard says: (Section SCSI-2 Rev. 10c Sect 5.6.20)
	 * 'The SAVE DATA POINTER message is sent from a target to
	 *  direct the initiator to copy the active data pointer to
	 *  the saved data pointer for the current I/O process.
	 */
	acornscsi_dma_cleanup(host);
	host->SCpnt->SCp = host->scsi.SCp;
	host->SCpnt->SCp.sent_command = 0;
	host->scsi.phase = PHASE_MSGIN;
	break;

    case RESTORE_POINTERS:
	/*
	 * ANSI standard says: (Section SCSI-2 Rev. 10c Sect 5.6.19)
	 * 'The RESTORE POINTERS message is sent from a target to
	 *  direct the initiator to copy the most recently saved
	 *  command, data, and status pointers for the I/O process
	 *  to the corresponding active pointers.  The command and
	 *  status pointers shall be restored to the beginning of
	 *  the present command and status areas.'
	 */
	acornscsi_dma_cleanup(host);
	host->scsi.SCp = host->SCpnt->SCp;
	host->scsi.phase = PHASE_MSGIN;
	break;

    case DISCONNECT:
	/*
	 * ANSI standard says: (Section SCSI-2 Rev. 10c Sect 6.4.2)
	 * 'On those occasions when an error or exception condition occurs
	 *  and the target elects to repeat the information transfer, the
	 *  target may repeat the transfer either issuing a RESTORE POINTERS
	 *  message or by disconnecting without issuing a SAVE POINTERS
	 *  message.  When reconnection is completed, the most recent
	 *  saved pointer values are restored.'
	 */
	acornscsi_dma_cleanup(host);
	host->scsi.phase = PHASE_DISCONNECT;
	break;

    case MESSAGE_REJECT:
#if 0 /* this isn't needed any more */
	/*
	 * If we were negociating sync transfer, we don't yet know if
	 * this REJECT is for the sync transfer or for the tagged queue/wide
	 * transfer.  Re-initiate sync transfer negociation now, and if
	 * we got a REJECT in response to SDTR, then it'll be set to DONE.
	 */
	if (host->device[host->SCpnt->device->id].sync_state == SYNC_SENT_REQUEST)
	    host->device[host->SCpnt->device->id].sync_state = SYNC_NEGOCIATE;
#endif

	/*
	 * If we have any messages waiting to go out, then assert ATN now
	 */
	if (msgqueue_msglength(&host->scsi.msgs))
	    acornscsi_sbic_issuecmd(host, CMND_ASSERTATN);

	switch (host->scsi.last_message) {
#ifdef CONFIG_SCSI_ACORNSCSI_TAGGED_QUEUE
	case HEAD_OF_QUEUE_TAG:
	case ORDERED_QUEUE_TAG:
	case SIMPLE_QUEUE_TAG:
	    /*
	     * ANSI standard says: (Section SCSI-2 Rev. 10c Sect 5.6.17)
	     *  If a target does not implement tagged queuing and a queue tag
	     *  message is received, it shall respond with a MESSAGE REJECT
	     *  message and accept the I/O process as if it were untagged.
	     */
	    printk(KERN_NOTICE "scsi%d.%c: disabling tagged queueing\n",
		    host->host->host_no, acornscsi_target(host));
	    host->SCpnt->device->simple_tags = 0;
	    set_bit(host->SCpnt->device->id * 8 + host->SCpnt->device->lun, host->busyluns);
	    break;
#endif
	case EXTENDED_MESSAGE | (EXTENDED_SDTR << 8):
	    /*
	     * Target can't handle synchronous transfers
	     */
	    printk(KERN_NOTICE "scsi%d.%c: Using asynchronous transfer\n",
		    host->host->host_no, acornscsi_target(host));
	    host->device[host->SCpnt->device->id].sync_xfer = SYNCHTRANSFER_2DBA;
	    host->device[host->SCpnt->device->id].sync_state = SYNC_ASYNCHRONOUS;
	    sbic_arm_write(host, SBIC_SYNCHTRANSFER, host->device[host->SCpnt->device->id].sync_xfer);
	    break;

	default:
	    break;
	}
	break;

    case QUEUE_FULL:
	/* TODO: target queue is full */
	break;

    case SIMPLE_QUEUE_TAG:
	/* tag queue reconnect... message[1] = queue tag.  Print something to indicate something happened! */
	printk("scsi%d.%c: reconnect queue tag %02X\n",
		host->host->host_no, acornscsi_target(host),
		message[1]);
	break;

    case EXTENDED_MESSAGE:
	switch (message[2]) {
#ifdef CONFIG_SCSI_ACORNSCSI_SYNC
	case EXTENDED_SDTR:
	    if (host->device[host->SCpnt->device->id].sync_state == SYNC_SENT_REQUEST) {
		/*
		 * We requested synchronous transfers.  This isn't quite right...
		 * We can only say if this succeeded if we proceed on to execute the
		 * command from this message.  If we get a MESSAGE PARITY ERROR,
		 * and the target retries fail, then we fallback to asynchronous mode
		 */
		host->device[host->SCpnt->device->id].sync_state = SYNC_COMPLETED;
		printk(KERN_NOTICE "scsi%d.%c: Using synchronous transfer, offset %d, %d ns\n",
			host->host->host_no, acornscsi_target(host),
			message[4], message[3] * 4);
		host->device[host->SCpnt->device->id].sync_xfer =
			calc_sync_xfer(message[3] * 4, message[4]);
	    } else {
		unsigned char period, length;
		/*
		 * Target requested synchronous transfers.  The agreement is only
		 * to be in operation AFTER the target leaves message out phase.
		 */
		acornscsi_sbic_issuecmd(host, CMND_ASSERTATN);
		period = max_t(unsigned int, message[3], sdtr_period / 4);
		length = min_t(unsigned int, message[4], sdtr_size);
		msgqueue_addmsg(&host->scsi.msgs, 5, EXTENDED_MESSAGE, 3,
				 EXTENDED_SDTR, period, length);
		host->device[host->SCpnt->device->id].sync_xfer =
			calc_sync_xfer(period * 4, length);
	    }
	    sbic_arm_write(host, SBIC_SYNCHTRANSFER, host->device[host->SCpnt->device->id].sync_xfer);
	    break;
#else
	    /* We do not accept synchronous transfers.  Respond with a
	     * MESSAGE_REJECT.
	     */
#endif

	case EXTENDED_WDTR:
	    /* The WD33C93A is only 8-bit.  We respond with a MESSAGE_REJECT
	     * to a wide data transfer request.
	     */
	default:
	    acornscsi_sbic_issuecmd(host, CMND_ASSERTATN);
	    msgqueue_flush(&host->scsi.msgs);
	    msgqueue_addmsg(&host->scsi.msgs, 1, MESSAGE_REJECT);
	    break;
	}
	break;

#ifdef CONFIG_SCSI_ACORNSCSI_LINK
    case LINKED_CMD_COMPLETE:
    case LINKED_FLG_CMD_COMPLETE:
	/*
	 * We don't support linked commands yet
	 */
	if (0) {
#if (DEBUG & DEBUG_LINK)
	    printk("scsi%d.%c: lun %d tag %d linked command complete\n",
		    host->host->host_no, acornscsi_target(host), host->SCpnt->tag);
#endif
	    /*
	     * A linked command should only terminate with one of these messages
	     * if there are more linked commands available.
	     */
	    if (!host->SCpnt->next_link) {
		printk(KERN_WARNING "scsi%d.%c: lun %d tag %d linked command complete, but no next_link\n",
			instance->host_no, acornscsi_target(host), host->SCpnt->tag);
		acornscsi_sbic_issuecmd(host, CMND_ASSERTATN);
		msgqueue_addmsg(&host->scsi.msgs, 1, ABORT);
	    } else {
		struct scsi_cmnd *SCpnt = host->SCpnt;

		acornscsi_dma_cleanup(host);

		host->SCpnt = host->SCpnt->next_link;
		host->SCpnt->tag = SCpnt->tag;
		SCpnt->result = DID_OK | host->scsi.SCp.Message << 8 | host->Scsi.SCp.Status;
		SCpnt->done(SCpnt);

		/* initialise host->SCpnt->SCp */
	    }
	    break;
	}
#endif

    default: /* reject message */
	printk(KERN_ERR "scsi%d.%c: unrecognised message %02X, rejecting\n",
		host->host->host_no, acornscsi_target(host),
		message[0]);
	acornscsi_sbic_issuecmd(host, CMND_ASSERTATN);
	msgqueue_flush(&host->scsi.msgs);
	msgqueue_addmsg(&host->scsi.msgs, 1, MESSAGE_REJECT);
	host->scsi.phase = PHASE_MSGIN;
	break;
    }
