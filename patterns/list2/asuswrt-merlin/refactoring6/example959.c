if (hostdata->connected
#ifdef REAL_DMA
		    && !hostdata->dmalen
#endif
		    && (!hostdata->time_expires || time_before_eq(hostdata->time_expires, jiffies))
		    ) {
			dprintk(NDEBUG_MAIN, ("scsi%d : main() : performing information transfer\n", instance->host_no));
			NCR5380_information_transfer(instance);
			dprintk(NDEBUG_MAIN, ("scsi%d : main() : done set false\n", instance->host_no));
			done = 0;
		} else
			break;
