if ((hostdata->options & (OPTION_DEBUG_INIT_ONLY|OPTION_DEBUG_PROBE_ONLY)) 
	|| ((hostdata->options & OPTION_DEBUG_TARGET_LIMIT) &&
	    !(hostdata->debug_lun_limit[cmd->device->id] & (1 << cmd->device->lun)))
#ifdef LINUX_1_2
	|| cmd->device->id > 7
#else
	|| cmd->device->id >= host->max_id
#endif
	|| cmd->device->id == host->this_id
	|| hostdata->state == STATE_DISABLED) {
	printk("scsi%d : disabled or bad target %d lun %d\n", host->host_no,
	    cmd->device->id, cmd->device->lun);
	cmd->result = (DID_BAD_TARGET << 16);
	done(cmd);
	local_irq_restore(flags);
	return 0;
    }
