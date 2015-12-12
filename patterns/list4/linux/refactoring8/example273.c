static int __crisv32_pinmux_alloc(int port, int first_pin, int last_pin,
				 enum pin_mode mode)
{
	int i;

	for (i = first_pin; i <= last_pin; i++) {
		if ((pins[port][i] != pinmux_none)
		    && (pins[port][i] != pinmux_gpio)
		    && (pins[port][i] != mode)) {
#ifdef DEBUG
			panic("Pinmux alloc failed!\n");
#endif
			return -EPERM;
		}
	}

	for (i = first_pin; i <= last_pin; i++)
		pins[port][i] = mode;

	crisv32_pinmux_set(port);

	return 0;
}
