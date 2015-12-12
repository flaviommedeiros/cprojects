switch (thisboard->bustype) {
	case isa_bustype:
		iobase = it->options[0];
		irq = it->options[1];
		share_irq = 0;
		break;
#ifdef CONFIG_COMEDI_PCI
	case pci_bustype:
		bus = it->options[0];
		slot = it->options[1];
		share_irq = 1;

		ret = pc236_find_pci(dev, bus, slot, &pci_dev);
		if (ret < 0)
			return ret;
		devpriv->pci_dev = pci_dev;
		break;
#endif /* CONFIG_COMEDI_PCI */
	default:
		printk(KERN_ERR
		       "comedi%d: %s: BUG! cannot determine board type!\n",
		       dev->minor, PC236_DRIVER_NAME);
		return -EINVAL;
		break;
	}
