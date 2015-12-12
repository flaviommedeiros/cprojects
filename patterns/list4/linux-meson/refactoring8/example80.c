void tvafe_init_reg(struct tvafe_cvd2_s *cvd2, struct tvafe_cvd2_mem_s *mem, enum tvin_port_e port, struct tvafe_pin_mux_s *pinmux)
{
	unsigned int i = 0;

	if ((port >= TVIN_PORT_VGA0) && (port <= TVIN_PORT_VGA7))
	{
		/**enable auto mode clock**/
		WRITE_CBUS_REG(HHI_TVFE_AUTOMODE_CLK_CNTL, 0x100);


		/** write top register don't after write 7740 register**/
		while (vga_top_reg_default[i][0] != 0xFFFFFFFF) {
			WRITE_APB_REG(vga_top_reg_default[i][0], vga_top_reg_default[i][1]);
			i++;
		}
		/** write 7740 register **/
		tvafe_adc_configure(TVIN_SIG_FMT_VGA_1024X768P_60HZ_D004);

		tvafe_top_config(TVIN_SIG_FMT_VGA_1024X768P_60HZ_D004);
	}
	else if ((port >= TVIN_PORT_COMP0) && (port <= TVIN_PORT_COMP7))
	{
		/**enable auto mode clock**/
		WRITE_CBUS_REG(HHI_TVFE_AUTOMODE_CLK_CNTL, 0x100);
		WRITE_CBUS_REG(HHI_VAFE_CLKOSCIN_CNTL, 0x100);

		/** write top register don't after write 7740 register**/
		while (comp_top_reg_default[i][0] != 0xFFFFFFFF) {
			WRITE_APB_REG(comp_top_reg_default[i][0], comp_top_reg_default[i][1]);
			i++;
		}
		/** write 7740 register **/
		tvafe_adc_configure(TVIN_SIG_FMT_COMP_720P_59HZ_D940);

		tvafe_top_config(TVIN_SIG_FMT_COMP_720P_59HZ_D940);
	}
	else if ((port >= TVIN_PORT_CVBS0) && (port <= TVIN_PORT_SVIDEO7))
	{
#ifdef CRYSTAL_25M
                WRITE_CBUS_REG(HHI_VAFE_CLKIN_CNTL, 0x703);
#endif
		tvafe_set_cvbs_default(cvd2, mem, port, pinmux);
		/*turn on/off av out*/
		tvafe_enable_avout(enableavout);
	}

	/* must reload mux if you change adc reg table!!! */
	tvafe_set_source_muxing(port, pinmux);

	pr_info("[tvafe..] %s ok.\n", __func__);

}
