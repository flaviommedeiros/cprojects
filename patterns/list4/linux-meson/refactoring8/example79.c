void tvafe_adc_configure(enum tvin_sig_fmt_e fmt)
{
	int i = 0;
	const unsigned char *buff_t = NULL;

	/*adc reset*/
	tvafe_adc_clear(TVAFE_ADC_CONFIGURE_INIT, 1);
	tvafe_adc_clear(TVAFE_ADC_CONFIGURE_NORMAL, 1);
	tvafe_adc_clear(TVAFE_ADC_CONFIGURE_RESET_ON, 1);

	if (fmt < TVIN_SIG_FMT_VGA_MAX && fmt > TVIN_SIG_FMT_NULL) // VGA formats
	{
		buff_t = adc_vga_table[fmt-TVIN_SIG_FMT_VGA_512X384P_60HZ_D147];
	}
	else if (fmt < TVIN_SIG_FMT_COMP_MAX && fmt > TVIN_SIG_FMT_VGA_THRESHOLD) // Component formats
	{
		buff_t = adc_component_table[fmt-TVIN_SIG_FMT_COMP_480P_60HZ_D000];
	}
	// CVBS formats
        else if(fmt < TVIN_SIG_FMT_CVBS_MAX && fmt > TVIN_SIG_FMT_HDMI_THRESHOLD)
	{
		buff_t = adc_cvbs_table;
	}
        else
        {
                pr_err("[tvafe..]%s: invaild fmt %s.\n",__func__,tvin_sig_fmt_str(fmt));
                return;
        }

	for (i=0; i<ADC_REG_NUM; i++)
	{
		WRITE_APB_REG(((ADC_BASE_ADD+i)<<2), (unsigned int)(buff_t[i]));
	}
	//set componet different phase base on board design
	if(fmt > TVIN_SIG_FMT_VGA_MAX && fmt < TVIN_SIG_FMT_COMP_MAX && enable_dphase)
	{
		WRITE_APB_REG_BITS(ADC_REG_56, comp_phase[fmt-TVIN_SIG_FMT_VGA_THRESHOLD -1],CLKPHASEADJ_BIT,CLKPHASEADJ_WID);
	}
	//for adc calibration clamping duration setting
	if (fmt < TVIN_SIG_FMT_COMP_MAX)
	{
		tvafe_adc_set_clamp_para(fmt);
	}

	/* adc config normal */
	tvafe_adc_clear(TVAFE_ADC_CONFIGURE_NORMAL, 0);
#ifdef TVAFE_DEBUG_PIN_ENABLE
	//debug setting
	// diable other mux on test pins 0~27 & 30
	WRITE_CBUS_REG(PERIPHS_PIN_MUX_0 , READ_CBUS_REG(PERIPHS_PIN_MUX_0 )&0xcff0ffdf);
	WRITE_CBUS_REG(PERIPHS_PIN_MUX_1 , READ_CBUS_REG(PERIPHS_PIN_MUX_1 )&0xfc017fff);
	WRITE_CBUS_REG(PERIPHS_PIN_MUX_2 , READ_CBUS_REG(PERIPHS_PIN_MUX_2 )&0xe001ffff);
	WRITE_CBUS_REG(PERIPHS_PIN_MUX_3 , READ_CBUS_REG(PERIPHS_PIN_MUX_3 )&0xfc000000);
	WRITE_CBUS_REG(PERIPHS_PIN_MUX_4 , READ_CBUS_REG(PERIPHS_PIN_MUX_4 )&0xff8007ff);
	WRITE_CBUS_REG(PERIPHS_PIN_MUX_6 , READ_CBUS_REG(PERIPHS_PIN_MUX_6 )&0xffffffbf);
	WRITE_CBUS_REG(PERIPHS_PIN_MUX_7 , READ_CBUS_REG(PERIPHS_PIN_MUX_7 )&0xff00003f);
	WRITE_CBUS_REG(PERIPHS_PIN_MUX_10, READ_CBUS_REG(PERIPHS_PIN_MUX_10)&0xffffffb3);
	// enable TVFE_TEST mux on test pins 0~27 & 30
	WRITE_CBUS_REG(PERIPHS_PIN_MUX_9 , 0x4fffffff);//
#endif

}
