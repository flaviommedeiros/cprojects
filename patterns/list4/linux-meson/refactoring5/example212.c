#ifdef CONFIG_SCSI_ACORNSCSI_TAGGED_QUEUE
if (tag)
	msgqueue_addmsg(&host->scsi.msgs, 2, ABORT_TAG, tag);
    else
#endif
	msgqueue_addmsg(&host->scsi.msgs, 1, ABORT);
