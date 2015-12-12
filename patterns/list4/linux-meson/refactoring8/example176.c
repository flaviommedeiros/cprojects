static char init_setup[] =
{
	0x8E,			/* length, prefetch on */
	0xC8,			/* fifo to 8, monitor off */
#ifdef CONFIG_VME
	0xc0,			/* don't save bad frames */
#else
	0x80,			/* don't save bad frames */
#endif
	0x2E,			/* No source address insertion, 8 byte preamble */
	0x00,			/* priority and backoff defaults */
	0x60,			/* interframe spacing */
	0x00,			/* slot time LSB */
	0xf2,			/* slot time and retries */
	0x00,			/* promiscuous mode */
	0x00,			/* collision detect */
	0x40,			/* minimum frame length */
	0xff,
	0x00,
	0x7f /*  *multi IA */ };
