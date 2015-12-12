#ifdef CONFIG_ARC_UBOOT_SUPPORT
if (uboot_tag && is_kernel((unsigned long)uboot_arg))
		panic("Invalid uboot arg\n");
