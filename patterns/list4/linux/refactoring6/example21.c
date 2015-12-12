if (hostdata->connected
#ifdef REAL_DMA
		    && !hostdata->dma_len
#endif
		    ) {
			local_irq_restore(flags);
			dprintk(NDEBUG_MAIN, "scsi%d: main: performing information transfer\n",
				    HOSTNO);
			NCR5380_information_transfer(instance);
			dprintk(NDEBUG_MAIN, "scsi%d: main: done set false\n", HOSTNO);
			done = 0;
		}
