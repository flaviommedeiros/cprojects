#ifdef CONFIG_BLK_DEV_IDEPCI
if (hwif->pci_dev && !hwif->pci_dev->vendor)
#endif	/* CONFIG_BLK_DEV_IDEPCI */
		{
			/*
			 * Probably not a shared PCI interrupt,
			 * so we can safely try to do something about it:
			 */
			unexpected_intr(irq, hwgroup);
#ifdef CONFIG_BLK_DEV_IDEPCI
		} else {
			/*
			 * Whack the status register, just in case
			 * we have a leftover pending IRQ.
			 */
			(void) hwif->INB(hwif->io_ports[IDE_STATUS_OFFSET]);
#endif /* CONFIG_BLK_DEV_IDEPCI */
		}
