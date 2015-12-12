if (ivg == (0xf &
#if defined(CONFIG_BF52x) || defined(CONFIG_BF538) \
	|| defined(CONFIG_BF539) || defined(CONFIG_BF51x)
			     bfin_read32((unsigned long *)SIC_IAR0 +
					 ((irqn % 32) >> 3) + ((irqn / 32) *
					 ((SIC_IAR4 - SIC_IAR0) / 4))) >> iar_shift)) {
#else
			     bfin_read32((unsigned long *)SIC_IAR0 +
					 (irqn >> 3)) >> iar_shift)
