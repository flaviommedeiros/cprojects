#if (LINUX_VERSION_CODE > 0x20605)
if ((pci_dev = pci_get_device(0x1022, 0x700c, NULL)))
#else
	if ((pci_dev = pci_find_device(0x1022, 0x700c, NULL)))
#endif
	{
		u32 val;

		/* Found AMD 762 North bridge */
		pci_read_config_dword(pci_dev, 0x4c, &val);
		if ((val & 0x02) == 0) {
			pci_write_config_dword(pci_dev, 0x4c, val | 0x02);
			printk(KERN_INFO "%s: Setting AMD762 Northbridge to enable PCI ordering compliance\n", bcm5700_driver);
		}
	}
