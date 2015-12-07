#ifdef CONFIG_STANDARD_DAB
if (state->fe->dtv_property_cache.delivery_system == STANDARD_DAB) {
						dib0090_write_reg(state, 0x02, (1 << 15) | (15 << 11) | (31 << 6) | (63));	/* cap value = 63 : narrow BB filter : Fc = 1.8MHz */
						dib0090_write_reg(state, 0x04, 0x0);
					} else
#endif
					{
						dib0090_write_reg(state, 0x02, (1 << 15) | (3 << 11) | (6 << 6) | (32));
						dib0090_write_reg(state, 0x04, 0x01);	/*0 = 1KHz ; 1 = 150Hz ; 2 = 50Hz ; 3 = 50KHz ; 4 = servo fast */
					}
