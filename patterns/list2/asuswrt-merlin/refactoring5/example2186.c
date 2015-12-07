#ifdef CONFIG_VGA_CONSOLE
if (!strcmp(consdev, "pcconsole0")) {
				setleds("pccn");
		} else
#endif
			return -ENODEV;
