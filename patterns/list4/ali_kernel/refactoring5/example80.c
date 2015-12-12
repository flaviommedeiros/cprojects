#ifdef CONFIG_PCI
if (s->cb_dev) {
			ret = pci_bus_alloc_resource(s->cb_dev->bus, res, num,
						     1, min, 0,
						     pcmcia_align, &data);
		} else
#endif
			ret = allocate_resource(&iomem_resource, res, num, min,
						max, 1, pcmcia_align, &data);
