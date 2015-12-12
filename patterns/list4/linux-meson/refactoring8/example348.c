static volatile unsigned long *data_out[NUM_PORTS] = {
	GIO_REG_WR_ADDR(rw_pa_dout),
	GIO_REG_WR_ADDR(rw_pb_dout),
	&led_dummy,
	GIO_REG_WR_ADDR(rw_pc_dout),
	GIO_REG_WR_ADDR(rw_pd_dout),
	GIO_REG_WR_ADDR(rw_pe_dout),
#ifdef CONFIG_ETRAX_VIRTUAL_GPIO
	&virtual_dummy,
#endif
};
