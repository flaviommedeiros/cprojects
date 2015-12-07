if (hostdata->connected
#ifdef REAL_DMA
		    && !hostdata->dma_len
#endif
		    ) {
			local_irq_restore(flags);
			MAIN_PRINTK("scsi%d: main: performing information transfer\n",
				    HOSTNO);
			NCR5380_information_transfer(instance);
			MAIN_PRINTK("scsi%d: main: done set false\n", HOSTNO);
			done = 0;
		}
