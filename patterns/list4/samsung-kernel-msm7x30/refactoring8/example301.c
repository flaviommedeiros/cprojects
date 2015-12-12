static unsigned long *dir_oe[NUM_PORTS] = {
	GIO_REG_WR_ADDR(rw_pa_oe),
	GIO_REG_WR_ADDR(rw_pb_oe),
	&led_dummy,
	GIO_REG_WR_ADDR(rw_pc_oe),
	&port_d_dummy,
#ifdef CONFIG_ETRAX_VIRTUAL_GPIO
	&port_e_dummy,
	&virtual_rw_pv_oe,
#endif
};
