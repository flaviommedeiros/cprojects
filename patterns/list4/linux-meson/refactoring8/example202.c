struct methods shadow_methods[] = {
#if defined(__powerpc__)
		{ "OpenFirmware", nouveau_bios_shadow_of, true, 0, 0, NULL },
#endif
		{ "PRAMIN", nouveau_bios_shadow_pramin, true, 0, 0, NULL },
		{ "PROM", nouveau_bios_shadow_prom, false, 0, 0, NULL },
		{ "ACPI", nouveau_bios_shadow_acpi, true, 0, 0, NULL },
		{ "PCIROM", nouveau_bios_shadow_pci, true, 0, 0, NULL },
		{ "PLATFORM", nouveau_bios_shadow_platform, true, 0, 0, NULL },
		{}
	};
