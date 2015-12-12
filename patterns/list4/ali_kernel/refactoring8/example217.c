static volatile unsigned long *dir_oe[NUM_PORTS] = {
	GIO_REG_WR_ADDR(rw_pa_oe),
	GIO_REG_WR_ADDR(rw_pb_oe),
	&led_dummy,
	GIO_REG_WR_ADDR(rw_pc_oe),
	GIO_REG_WR_ADDR(rw_pd_oe),
	GIO_REG_WR_ADDR(rw_pe_oe),
#ifdef CONFIG_ETRAX_VIRTUAL_GPIO
	&virtual_rw_pv_oe,
#endif
};
