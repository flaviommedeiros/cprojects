static struct of_bus of_busses[] = {
#ifdef CONFIG_PCI
	/* PCI */
	{
		.name = "pci",
		.addresses = "assigned-addresses",
		.match = of_bus_pci_match,
		.count_cells = of_bus_pci_count_cells,
		.map = of_bus_pci_map,
		.translate = of_bus_pci_translate,
		.get_flags = of_bus_pci_get_flags,
	},
#endif /* CONFIG_PCI */
	/* ISA */
	{
		.name = "isa",
		.addresses = "reg",
		.match = of_bus_isa_match,
		.count_cells = of_bus_isa_count_cells,
		.map = of_bus_isa_map,
		.translate = of_bus_isa_translate,
		.get_flags = of_bus_isa_get_flags,
	},
	/* Default */
	{
		.name = "default",
		.addresses = "reg",
		.match = NULL,
		.count_cells = of_bus_default_count_cells,
		.map = of_bus_default_map,
		.translate = of_bus_default_translate,
		.get_flags = of_bus_default_get_flags,
	},
};
