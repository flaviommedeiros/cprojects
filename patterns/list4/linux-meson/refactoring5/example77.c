#ifdef CONFIG_ATA_BMDMA
if (bmdma)
		/* prepare and activate BMDMA host */
		rc = ata_pci_bmdma_prepare_host(pdev, ppi, &host);
	else
#endif
		/* prepare and activate SFF host */
		rc = ata_pci_sff_prepare_host(pdev, ppi, &host);
