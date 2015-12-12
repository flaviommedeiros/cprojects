#ifdef CONFIG_COMEDI_PCI
if (pci_dev) {

		ret = comedi_pci_enable(pci_dev, PC236_DRIVER_NAME);
		if (ret < 0) {
			printk(KERN_ERR
			       "comedi%d: error! cannot enable PCI device and request regions!\n",
			       dev->minor);
			return ret;
		}
		devpriv->lcr_iobase = pci_resource_start(pci_dev, 1);
		iobase = pci_resource_start(pci_dev, 2);
		irq = pci_dev->irq;
	} else
#endif
	{
		ret = pc236_request_region(dev->minor, iobase, PC236_IO_SIZE);
		if (ret < 0) {
			return ret;
		}
	}
