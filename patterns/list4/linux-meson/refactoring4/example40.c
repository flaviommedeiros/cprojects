#if defined(DEBUG_INTERRUPT)
if (SCpnt->result || do_trace)
#else
   if ((spp->adapter_status != ASOK && HD(j)->iocount >  1000) ||
       (spp->adapter_status != ASOK &&
        spp->adapter_status != ASST && HD(j)->iocount <= 1000) ||
        do_trace || msg_byte(spp->target_status))
#endif
      scmd_printk(KERN_INFO, SCpnt, "ihdlr, mbox %2d, err 0x%x:%x,"\
             " reg 0x%x, count %d.\n",
             i, spp->adapter_status, spp->target_status,
             reg, HD(j)->iocount);
