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
	    set_bit(host->SCpnt->device->id * 8 +
		    (u8)(host->SCpnt->device->lun & 0x7), host->busyluns);
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
