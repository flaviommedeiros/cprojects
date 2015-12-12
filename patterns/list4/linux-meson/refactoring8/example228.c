static const struct attribute_group *pci_dev_attr_groups[] = {
	&pci_dev_attr_group,
#ifdef CONFIG_PCI_IOV
	&sriov_dev_attr_group,
#endif
	NULL,
};
