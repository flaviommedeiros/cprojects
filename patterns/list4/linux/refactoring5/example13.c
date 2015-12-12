#ifdef CONFIG_PNP
if (isapnp && chip->mc_base)
		/* PnP resource gives the least 10 bits */
		chip->mc_base |= 0xc00;
	else
#endif	/* CONFIG_PNP */
	{
		chip->mc_base = 0xf8c;
		chip->mc_base_size = opti9xx_mc_size[hardware];
	}
