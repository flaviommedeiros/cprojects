static const struct snd_kcontrol_new rt5640_snd_controls[] = {
	/* Speaker Output Volume */
//	SOC_DOUBLE("Speaker Playback Switch", RT5640_SPK_VOL,
//		RT5640_L_MUTE_SFT, RT5640_R_MUTE_SFT, 1, 1),
//	SOC_DOUBLE_EXT_TLV("Speaker Playback Volume", RT5640_SPK_VOL,
//		RT5640_L_VOL_SFT, RT5640_R_VOL_SFT, RT5640_VOL_RSCL_RANGE, 0,
//		rt5640_vol_rescale_get, rt5640_vol_rescale_put, out_vol_tlv),
	/* Headphone Output Volume */
	SOC_DOUBLE("HP Playback Switch", RT5640_HP_VOL,
		RT5640_L_MUTE_SFT, RT5640_R_MUTE_SFT, 1, 1),
	SOC_DOUBLE_EXT_TLV("HP Playback Volume", RT5640_HP_VOL,
		RT5640_L_VOL_SFT, RT5640_R_VOL_SFT, RT5640_VOL_RSCL_RANGE, 0,
		rt5640_vol_rescale_get, rt5640_vol_rescale_put, out_vol_tlv),
	/* OUTPUT Control */
	SOC_DOUBLE("OUT Playback Switch", RT5640_OUTPUT,
		RT5640_L_MUTE_SFT, RT5640_R_MUTE_SFT, 1, 1),
	SOC_DOUBLE("OUT Channel Switch", RT5640_OUTPUT,
		RT5640_VOL_L_SFT, RT5640_VOL_R_SFT, 1, 1),
	SOC_DOUBLE_TLV("OUT Playback Volume", RT5640_OUTPUT,
		RT5640_L_VOL_SFT, RT5640_R_VOL_SFT, 39, 1, out_vol_tlv),
	/* MONO Output Control */
	SOC_SINGLE("Mono Playback Switch", RT5640_MONO_OUT,
				RT5640_L_MUTE_SFT, 1, 1),
	/* DAC Digital Volume */
	SOC_DOUBLE("DAC2 Playback Switch", RT5640_DAC2_CTRL,
		RT5640_M_DAC_L2_VOL_SFT, RT5640_M_DAC_R2_VOL_SFT, 1, 1),
	SOC_DOUBLE_TLV("DAC1 Playback Volume", RT5640_DAC1_DIG_VOL,
			RT5640_L_VOL_SFT, RT5640_R_VOL_SFT,
			175, 0, dac_vol_tlv),
	SOC_DOUBLE_TLV("Mono DAC Playback Volume", RT5640_DAC2_DIG_VOL,
			RT5640_L_VOL_SFT, RT5640_R_VOL_SFT,
			175, 0, dac_vol_tlv),
	/* IN1/IN2 Control */
	SOC_ENUM("IN1 Mode Control",  rt5640_in1_mode_enum),
	SOC_SINGLE_TLV("IN1 Boost", RT5640_IN1_IN2,
		RT5640_BST_SFT1, 8, 0, bst_tlv),
	SOC_ENUM("IN2 Mode Control", rt5640_in2_mode_enum),
	SOC_SINGLE_TLV("IN2 Boost", RT5640_IN3_IN4,
		RT5640_BST_SFT2, 8, 0, bst_tlv),
	/* INL/INR Volume Control */
	SOC_DOUBLE_TLV("IN Capture Volume", RT5640_INL_INR_VOL,
			RT5640_INL_VOL_SFT, RT5640_INR_VOL_SFT,
			31, 1, in_vol_tlv),
	/* ADC Digital Volume Control */
	SOC_DOUBLE("ADC Capture Switch", RT5640_ADC_DIG_VOL,
		RT5640_L_MUTE_SFT, RT5640_R_MUTE_SFT, 1, 1),
	SOC_DOUBLE_TLV("ADC Capture Volume", RT5640_ADC_DIG_VOL,
			RT5640_L_VOL_SFT, RT5640_R_VOL_SFT,
			127, 0, adc_vol_tlv),
	SOC_DOUBLE_TLV("Mono ADC Capture Volume", RT5640_ADC_DATA,
			RT5640_L_VOL_SFT, RT5640_R_VOL_SFT,
			127, 0, adc_vol_tlv),
	/* ADC Boost Volume Control */
	SOC_DOUBLE_TLV("ADC Boost Gain", RT5640_ADC_BST_VOL,
			RT5640_ADC_L_BST_SFT, RT5640_ADC_R_BST_SFT,
			3, 0, adc_bst_tlv),
	/* Class D speaker gain ratio */
	SOC_ENUM("Class D SPK Ratio Control", rt5640_clsd_spk_ratio_enum),
	/* DMIC */
	SOC_ENUM_EXT("DMIC Switch", rt5640_dmic_enum,
		rt5640_dmic_get, rt5640_dmic_put),
	SOC_ENUM_EXT("DMIC1 Source Switch", rt5640_dmic1_src_enum,
		rt5640_dmic1_src_get, rt5640_dmic1_src_put),

	SOC_ENUM("ADC IF1 Data Switch", rt5640_if1_adc_enum),
	SOC_ENUM("DAC IF1 Data Switch", rt5640_if1_dac_enum),
	SOC_ENUM("ADC IF2 Data Switch", rt5640_if2_adc_enum),
	SOC_ENUM("DAC IF2 Data Switch", rt5640_if2_dac_enum),
#ifdef RT5640_REG_RW
	{
		.iface = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Register Control",
		.info = rt5640_regctl_info,
		.get = rt5640_regctl_get,
		.put = rt5640_regctl_put,
	},
#endif
};
