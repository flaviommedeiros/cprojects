static const struct pci_device_id bnxt_pci_tbl[] = {
	{ PCI_VDEVICE(BROADCOM, 0x16c9), .driver_data = BCM57302 },
	{ PCI_VDEVICE(BROADCOM, 0x16ca), .driver_data = BCM57304 },
	{ PCI_VDEVICE(BROADCOM, 0x16d1), .driver_data = BCM57404 },
	{ PCI_VDEVICE(BROADCOM, 0x16d2), .driver_data = BCM57406 },
#ifdef CONFIG_BNXT_SRIOV
	{ PCI_VDEVICE(BROADCOM, 0x16cb), .driver_data = BCM57304_VF },
	{ PCI_VDEVICE(BROADCOM, 0x16d3), .driver_data = BCM57404_VF },
#endif
	{ 0 }
};
