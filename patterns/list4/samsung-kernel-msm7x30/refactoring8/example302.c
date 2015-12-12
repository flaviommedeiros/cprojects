int
crisv32_pinmux_alloc(int port, int first_pin, int last_pin, enum pin_mode mode)
{
	int i;
	unsigned long flags;

	crisv32_pinmux_init();

	if (port > PORTS || port < 0)
		return -EINVAL;

	spin_lock_irqsave(&pinmux_lock, flags);

	for (i = first_pin; i <= last_pin; i++) {
		if ((pins[port][i] != pinmux_none)
		    && (pins[port][i] != pinmux_gpio)
		    && (pins[port][i] != mode)) {
			spin_unlock_irqrestore(&pinmux_lock, flags);
#ifdef DEBUG
			panic("Pinmux alloc failed!\n");
#endif
			return -EPERM;
		}
	}

	for (i = first_pin; i <= last_pin; i++)
		pins[port][i] = mode;

	crisv32_pinmux_set(port);

	spin_unlock_irqrestore(&pinmux_lock, flags);

	return 0;
}
