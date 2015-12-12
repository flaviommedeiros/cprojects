#if defined(MCFGPIO_IRQ_MIN)
if ((offset >= MCFGPIO_IRQ_MIN) && (offset < MCFGPIO_IRQ_MAX))
#else
	if (offset < MCFGPIO_IRQ_MAX)
#endif
		return MCFGPIO_IRQ_VECBASE + offset;
	else
		return -EINVAL;
