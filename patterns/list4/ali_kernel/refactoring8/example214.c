static volatile unsigned long *data_in[NUM_PORTS] = {
	GIO_REG_RD_ADDR(r_pa_din),
	GIO_REG_RD_ADDR(r_pb_din),
	&led_dummy,
	GIO_REG_RD_ADDR(r_pc_din),
	GIO_REG_RD_ADDR(r_pd_din),
	GIO_REG_RD_ADDR(r_pe_din),
#ifdef CONFIG_ETRAX_VIRTUAL_GPIO
	&virtual_dummy,
#endif
};
