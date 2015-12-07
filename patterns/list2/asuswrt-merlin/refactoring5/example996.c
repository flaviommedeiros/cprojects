#ifdef CONFIG_SIBYTE_SB1250_DUART
if (!strcmp(consdev, "uart0")) {
			setleds("u0cn");
		} else if (!strcmp(consdev, "uart1")) {
			setleds("u1cn");
		} else
#endif
#ifdef CONFIG_VGA_CONSOLE
		       if (!strcmp(consdev, "pcconsole0")) {
				setleds("pccn");
		} else
#endif
			return -ENODEV;
