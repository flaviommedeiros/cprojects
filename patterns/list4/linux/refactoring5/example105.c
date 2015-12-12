#ifdef CONFIG_PCI_IOV
if (pe->flags & PNV_IODA_PE_VF)
			parent = pe->parent_dev;
		else
#endif /* CONFIG_PCI_IOV */
			parent = pe->pdev->bus->self;
