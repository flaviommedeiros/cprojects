#ifdef CONFIG_COMEDI_PCI
if (pci_dev) {
		ret = comedi_pci_enable(pci_dev, PC263_DRIVER_NAME);
		if (ret < 0) {
			printk(KERN_ERR
			       "comedi%d: error! cannot enable PCI device and request regions!\n",
			       dev->minor);
			return ret;
		}
		iobase = pci_resource_start(pci_dev, 2);
	} else
#endif
	{
		ret = pc263_request_region(dev->minor, iobase, PC263_IO_SIZE);
		if (ret < 0) {
			return ret;
		}
	}
