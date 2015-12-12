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
