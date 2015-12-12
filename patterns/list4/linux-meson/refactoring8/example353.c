static unsigned long *data_out[NUM_PORTS] = {
	GIO_REG_WR_ADDR(rw_pa_dout),
	GIO_REG_WR_ADDR(rw_pb_dout),
	&led_dummy,
	GIO_REG_WR_ADDR(rw_pc_dout),
	&port_d_dummy,
#ifdef CONFIG_ETRAX_VIRTUAL_GPIO
	&port_e_dummy,
	&virtual_dummy,
#endif
};
