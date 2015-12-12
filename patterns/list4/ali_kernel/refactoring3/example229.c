switch (ssr) {
#ifdef NONSTANDARD
	case 0x8a:			/* -> PHASE_COMMAND, PHASE_COMMANDPAUSED	*/
	    /* SELECTION -> COMMAND */
	    acornscsi_sendcommand(host);
	    break;

	case 0x8b:			/* -> PHASE_STATUS				*/
	    /* SELECTION -> STATUS */
	    acornscsi_readstatusbyte(host);
	    host->scsi.phase = PHASE_STATUSIN;
	    break;
#endif

	case 0x8e:			/* -> PHASE_MSGOUT				*/
	    /* SELECTION ->MESSAGE OUT */
	    host->scsi.phase = PHASE_MSGOUT;
	    acornscsi_buildmessages(host);
	    acornscsi_sendmessage(host);
	    break;

	/* these should not happen */
	case 0x85:			/* target disconnected				*/
	    acornscsi_done(host, &host->SCpnt, DID_ERROR);
	    break;

	default:
	    printk(KERN_ERR "scsi%d.%c: PHASE_CONNECTED, SSR %02X?\n",
		    host->host->host_no, acornscsi_target(host), ssr);
	    acornscsi_dumplog(host, host->SCpnt ? host->SCpnt->device->id : 8);
	    acornscsi_abortcmd(host, host->SCpnt->tag);
	}
