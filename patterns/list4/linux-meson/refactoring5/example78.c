#ifdef CONFIG_ATA_BMDMA
if (bmdma) {
		pci_set_master(pdev);
		rc = ata_pci_sff_activate_host(host, ata_bmdma_interrupt, sht);
	} else
#endif
		rc = ata_pci_sff_activate_host(host, ata_sff_interrupt, sht);
