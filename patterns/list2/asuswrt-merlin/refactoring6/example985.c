if (!strncmp((char *)&boot_params.efi_info.efi_loader_signature,
#ifdef CONFIG_X86_32
		     "EL32",
#else
		     "EL64",
#endif
	 4)) {
		efi_enabled = 1;
		efi_reserve_early();
	}
