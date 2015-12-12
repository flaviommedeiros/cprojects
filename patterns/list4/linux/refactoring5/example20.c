#ifdef CONFIG_PCI_IOV
if (pci_dev->is_virtfn) {
			add->flags = XEN_PCI_DEV_VIRTFN;
			add->physfn.bus = physfn->bus->number;
			add->physfn.devfn = physfn->devfn;
		} else
#endif
		if (pci_ari_enabled(pci_dev->bus) && PCI_SLOT(pci_dev->devfn))
			add->flags = XEN_PCI_DEV_EXTFN;
