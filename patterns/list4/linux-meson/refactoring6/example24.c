if ((
#if !defined(MODULE) /* pci_domains_supported is not being exported */ \
    || !defined(CONFIG_PCI_DOMAINS)
	     !pci_domains_supported ? domain :
#endif
	     domain < 0 || domain > 0xffff)
	    || bus < 0 || bus > 0xff
	    || PCI_SLOT(devfn) != slot
	    || PCI_FUNC(devfn) != func)
		return -EINVAL;
