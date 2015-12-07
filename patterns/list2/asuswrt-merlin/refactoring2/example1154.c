#ifdef NCR5380_STATS
if (cmd->request_bufflen > NCR5380_STAT_LIMIT)
# endif
	switch (cmd->cmnd[0])
	{
	    case WRITE:
	    case WRITE_6:
	    case WRITE_10:
		hostdata->time_write[cmd->device->id] -= (jiffies - hostdata->timebase);
		hostdata->bytes_write[cmd->device->id] += cmd->request_bufflen;
		hostdata->pendingw++;
		break;
	    case READ:
	    case READ_6:
	    case READ_10:
		hostdata->time_read[cmd->device->id] -= (jiffies - hostdata->timebase);
		hostdata->bytes_read[cmd->device->id] += cmd->request_bufflen;
		hostdata->pendingr++;
		break;
	}
