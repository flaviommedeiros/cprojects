static struct mxl111sf_reg_ctrl_info init_i2s[] = {
		{0x1b, 0xff, 0x1e}, /* pin mux mode, Choose 656/I2S input */
		{0x15, 0x60, 0x60}, /* Enable I2S */
		{0x17, 0xe0, 0x20}, /* Input, MPEG MODE USB,
				       Inverted 656 Clock, I2S_SOFT_RESET,
				       0 : Normal operation, 1 : Reset State */
#if 0
		{0x12, 0x01, 0x00}, /* AUDIO_IRQ_CLR (Overflow Indicator) */
#endif
		{0x00, 0xff, 0x02}, /* Change to Control Page */
		{0x26, 0x0d, 0x0d}, /* I2S_MODE & BT656_SRC_SEL for FPGA only */
		{0x00, 0xff, 0x00},
		{0,    0,    0}
	};
