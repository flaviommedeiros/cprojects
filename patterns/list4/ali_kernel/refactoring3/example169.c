switch(tig_ver){
#ifndef CONFIG_ACENIC_OMIT_TIGON_I
	case 4:
	case 5:
		printk(KERN_INFO "  Tigon I  (Rev. %i), Firmware: %i.%i.%i, ",
		       tig_ver, ap->firmware_major, ap->firmware_minor,
		       ap->firmware_fix);
		writel(0, &regs->LocalCtrl);
		ap->version = 1;
		ap->tx_ring_entries = TIGON_I_TX_RING_ENTRIES;
		break;
#endif
	case 6:
		printk(KERN_INFO "  Tigon II (Rev. %i), Firmware: %i.%i.%i, ",
		       tig_ver, ap->firmware_major, ap->firmware_minor,
		       ap->firmware_fix);
		writel(readl(&regs->CpuBCtrl) | CPU_HALT, &regs->CpuBCtrl);
		readl(&regs->CpuBCtrl);		/* PCI write posting */
		/*
		 * The SRAM bank size does _not_ indicate the amount
		 * of memory on the card, it controls the _bank_ size!
		 * Ie. a 1MB AceNIC will have two banks of 512KB.
		 */
		writel(SRAM_BANK_512K, &regs->LocalCtrl);
		writel(SYNC_SRAM_TIMING, &regs->MiscCfg);
		ap->version = 2;
		ap->tx_ring_entries = MAX_TX_RING_ENTRIES;
		break;
	default:
		printk(KERN_WARNING "  Unsupported Tigon version detected "
		       "(%i)\n", tig_ver);
		ecode = -ENODEV;
		goto init_error;
	}
