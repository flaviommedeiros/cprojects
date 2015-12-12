#ifdef CONFIG_COMEDI_PCI
if (devpriv->pci_dev) {
			if (dev->iobase) {
				comedi_pci_disable(devpriv->pci_dev);
			}
			pci_dev_put(devpriv->pci_dev);
		} else
#endif
		{
			if (dev->iobase) {
				release_region(dev->iobase, DIO200_IO_SIZE);
			}
		}
