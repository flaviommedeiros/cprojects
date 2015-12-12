static struct resource smc91x_resources[] = {
	[0] = DEFINE_RES_MEM(PLEB_ETH0_P, 0x04000000),
#if 0 /* Autoprobe instead, to get rising/falling edge characteristic right */
	[1] = DEFINE_RES_IRQ(IRQ_GPIO_ETH0_IRQ),
#endif
};
