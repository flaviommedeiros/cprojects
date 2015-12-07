#ifdef CONFIG_PCI
if (dev->bus == &pci_bus_type)
		node = pcibus_to_node(to_pci_dev(dev)->bus);
	else
#endif
		node = numa_node_id();
