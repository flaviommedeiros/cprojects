switch (reboot_type) {
		case BOOT_KBD:
			mach_reboot_fixups(); /* for board specific fixups */

			for (i = 0; i < 10; i++) {
				kb_wait();
				udelay(50);
				outb(0xfe, 0x64); /* pulse reset low */
				udelay(50);
			}
			if (attempt == 0 && orig_reboot_type == BOOT_ACPI) {
				attempt = 1;
				reboot_type = BOOT_ACPI;
			} else {
				reboot_type = BOOT_TRIPLE;
			}
			break;

		case BOOT_TRIPLE:
			load_idt(&no_idt);
			__asm__ __volatile__("int3");

			reboot_type = BOOT_KBD;
			break;

#ifdef CONFIG_X86_32
		case BOOT_BIOS:
			machine_real_restart(jump_to_bios, sizeof(jump_to_bios));

			reboot_type = BOOT_KBD;
			break;
#endif

		case BOOT_ACPI:
			acpi_reboot();
			reboot_type = BOOT_KBD;
			break;

		case BOOT_EFI:
			if (efi_enabled)
				efi.reset_system(reboot_mode ?
						 EFI_RESET_WARM :
						 EFI_RESET_COLD,
						 EFI_SUCCESS, 0, NULL);
			reboot_type = BOOT_KBD;
			break;

		case BOOT_CF9:
			port_cf9_safe = true;
			/* fall through */

		case BOOT_CF9_COND:
			if (port_cf9_safe) {
				u8 cf9 = inb(0xcf9) & ~6;
				outb(cf9|2, 0xcf9); /* Request hard reset */
				udelay(50);
				outb(cf9|6, 0xcf9); /* Actually do the reset */
				udelay(50);
			}
			reboot_type = BOOT_KBD;
			break;
		}
