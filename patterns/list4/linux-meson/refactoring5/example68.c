#ifdef CONFIG_PCI
if (ctrlr->bus == &pci_bus_type) {
		const struct pci_dev *pdev = to_pci_dev(ctrlr);

		dbgp.u.pci.seg = pci_domain_nr(pdev->bus);
		dbgp.u.pci.bus = pdev->bus->number;
		dbgp.u.pci.devfn = pdev->devfn;
		dbgp.bus = PHYSDEVOP_DBGP_BUS_PCI;
	} else
#endif
		dbgp.bus = PHYSDEVOP_DBGP_BUS_UNKNOWN;
