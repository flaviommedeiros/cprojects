#if defined(DEBUG_INTERRUPT)
if (SCpnt->result || do_trace)
#else
	if ((spp->adapter_status != ASOK && ha->iocount > 1000) ||
	    (spp->adapter_status != ASOK &&
	     spp->adapter_status != ASST && ha->iocount <= 1000) ||
	    do_trace || msg_byte(spp->target_status))
#endif
		scmd_printk(KERN_INFO, SCpnt, "ihdlr, mbox %2d, err 0x%x:%x,"
		       " pid %ld, reg 0x%x, count %d.\n",
		       i, spp->adapter_status, spp->target_status,
		       SCpnt->serial_number, reg, ha->iocount);
