static const struct pci_device_id siimage_pci_tbl[] = {
	{ PCI_VDEVICE(CMD, PCI_DEVICE_ID_SII_680),    0 },
#ifdef CONFIG_BLK_DEV_IDE_SATA
	{ PCI_VDEVICE(CMD, PCI_DEVICE_ID_SII_3112),   1 },
	{ PCI_VDEVICE(CMD, PCI_DEVICE_ID_SII_1210SA), 1 },
#endif
	{ 0, },
};
