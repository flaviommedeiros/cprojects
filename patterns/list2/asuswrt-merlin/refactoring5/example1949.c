#ifdef CONFIG_PCI
if (s->cb_dev) {
		ret = pci_bus_alloc_resource(s->cb_dev->bus, res, num, 1,
					     min, 0, pcmcia_align, &data);
	} else
#endif
		ret = allocate_resource(&ioport_resource, res, num, min, ~0UL,
					1, pcmcia_align, &data);
