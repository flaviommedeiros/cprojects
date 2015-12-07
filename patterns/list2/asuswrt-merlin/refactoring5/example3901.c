#ifdef CONFIG_PNP
if (isapnp && chip->mc_base)
		/* PnP resource gives the least 10 bits */
		chip->mc_base |= 0xc00;
	else
#endif
		chip->mc_base = 0xf8c;
