switch (type) {
	case ASIC_LANCE:
		dev->base_addr = CKSEG1ADDR(dec_kn_slot_base + IOASIC_LANCE);

		/* buffer space for the on-board LANCE shared memory */
		/*
		 * FIXME: ugly hack!
		 */
		dev->mem_start = CKSEG1ADDR(0x00020000);
		dev->mem_end = dev->mem_start + 0x00020000;
		dev->irq = dec_interrupt[DEC_IRQ_LANCE];
		esar_base = CKSEG1ADDR(dec_kn_slot_base + IOASIC_ESAR);

		/* Workaround crash with booting KN04 2.1k from Disk */
		memset((void *)dev->mem_start, 0,
		       dev->mem_end - dev->mem_start);

		/*
		 * setup the pointer arrays, this sucks [tm] :-(
		 */
		for (i = 0; i < RX_RING_SIZE; i++) {
			lp->rx_buf_ptr_cpu[i] =
				(char *)(dev->mem_start + 2 * BUF_OFFSET_CPU +
					 2 * i * RX_BUFF_SIZE);
			lp->rx_buf_ptr_lnc[i] =
				(BUF_OFFSET_LNC + i * RX_BUFF_SIZE);
		}
		for (i = 0; i < TX_RING_SIZE; i++) {
			lp->tx_buf_ptr_cpu[i] =
				(char *)(dev->mem_start + 2 * BUF_OFFSET_CPU +
					 2 * RX_RING_SIZE * RX_BUFF_SIZE +
					 2 * i * TX_BUFF_SIZE);
			lp->tx_buf_ptr_lnc[i] =
				(BUF_OFFSET_LNC +
				 RX_RING_SIZE * RX_BUFF_SIZE +
				 i * TX_BUFF_SIZE);
		}

		/* Setup I/O ASIC LANCE DMA.  */
		lp->dma_irq = dec_interrupt[DEC_IRQ_LANCE_MERR];
		ioasic_write(IO_REG_LANCE_DMA_P,
			     CPHYSADDR(dev->mem_start) << 3);

		break;
#ifdef CONFIG_TC
	case PMAD_LANCE:
		dev_set_drvdata(bdev, dev);

		start = to_tc_dev(bdev)->resource.start;
		len = to_tc_dev(bdev)->resource.end - start + 1;
		if (!request_mem_region(start, len, dev_name(bdev))) {
			printk(KERN_ERR
			       "%s: Unable to reserve MMIO resource\n",
			       dev_name(bdev));
			ret = -EBUSY;
			goto err_out_dev;
		}

		dev->mem_start = CKSEG1ADDR(start);
		dev->mem_end = dev->mem_start + 0x100000;
		dev->base_addr = dev->mem_start + 0x100000;
		dev->irq = to_tc_dev(bdev)->interrupt;
		esar_base = dev->mem_start + 0x1c0002;
		lp->dma_irq = -1;

		for (i = 0; i < RX_RING_SIZE; i++) {
			lp->rx_buf_ptr_cpu[i] =
				(char *)(dev->mem_start + BUF_OFFSET_CPU +
					 i * RX_BUFF_SIZE);
			lp->rx_buf_ptr_lnc[i] =
				(BUF_OFFSET_LNC + i * RX_BUFF_SIZE);
		}
		for (i = 0; i < TX_RING_SIZE; i++) {
			lp->tx_buf_ptr_cpu[i] =
				(char *)(dev->mem_start + BUF_OFFSET_CPU +
					 RX_RING_SIZE * RX_BUFF_SIZE +
					 i * TX_BUFF_SIZE);
			lp->tx_buf_ptr_lnc[i] =
				(BUF_OFFSET_LNC +
				 RX_RING_SIZE * RX_BUFF_SIZE +
				 i * TX_BUFF_SIZE);
		}

		break;
#endif
	case PMAX_LANCE:
		dev->irq = dec_interrupt[DEC_IRQ_LANCE];
		dev->base_addr = CKSEG1ADDR(KN01_SLOT_BASE + KN01_LANCE);
		dev->mem_start = CKSEG1ADDR(KN01_SLOT_BASE + KN01_LANCE_MEM);
		dev->mem_end = dev->mem_start + KN01_SLOT_SIZE;
		esar_base = CKSEG1ADDR(KN01_SLOT_BASE + KN01_ESAR + 1);
		lp->dma_irq = -1;

		/*
		 * setup the pointer arrays, this sucks [tm] :-(
		 */
		for (i = 0; i < RX_RING_SIZE; i++) {
			lp->rx_buf_ptr_cpu[i] =
				(char *)(dev->mem_start + 2 * BUF_OFFSET_CPU +
					 2 * i * RX_BUFF_SIZE);
			lp->rx_buf_ptr_lnc[i] =
				(BUF_OFFSET_LNC + i * RX_BUFF_SIZE);
		}
		for (i = 0; i < TX_RING_SIZE; i++) {
			lp->tx_buf_ptr_cpu[i] =
				(char *)(dev->mem_start + 2 * BUF_OFFSET_CPU +
					 2 * RX_RING_SIZE * RX_BUFF_SIZE +
					 2 * i * TX_BUFF_SIZE);
			lp->tx_buf_ptr_lnc[i] =
				(BUF_OFFSET_LNC +
				 RX_RING_SIZE * RX_BUFF_SIZE +
				 i * TX_BUFF_SIZE);
		}

		break;

	default:
		printk(KERN_ERR "%s: declance_init called with unknown type\n",
			name);
		ret = -ENODEV;
		goto err_out_dev;
	}
