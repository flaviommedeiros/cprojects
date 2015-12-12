struct device_attribute pcibus_dev_attrs[] = {
#ifdef CONFIG_HOTPLUG
	__ATTR(rescan, (S_IWUSR|S_IWGRP), NULL, dev_bus_rescan_store),
#endif
	__ATTR(cpuaffinity, S_IRUGO, pci_bus_show_cpumaskaffinity, NULL),
	__ATTR(cpulistaffinity, S_IRUGO, pci_bus_show_cpulistaffinity, NULL),
	__ATTR_NULL,
};
