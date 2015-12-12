static const struct snd_soc_dapm_widget es8323_dapm_widgets[] = {
 // DAC Part
 SND_SOC_DAPM_MIXER("Left Mixer", SND_SOC_NOPM, 0, 0, &es8323_left_mixer_controls[0], ARRAY_SIZE(es8323_left_mixer_controls)),
 SND_SOC_DAPM_MIXER("Right Mixer", SND_SOC_NOPM, 0, 0, &es8323_right_mixer_controls[0], ARRAY_SIZE(es8323_right_mixer_controls)),

 SND_SOC_DAPM_MUX("Left Line Mux", SND_SOC_NOPM, 0, 0, &es8323_left_line_controls),
 SND_SOC_DAPM_MUX("Right Line Mux", SND_SOC_NOPM, 0, 0, &es8323_right_line_controls),

 SND_SOC_DAPM_DAC("Left DAC" , "Left Playback" , ES8323_DACCONTROL38, 7, 1),
 SND_SOC_DAPM_DAC("Right DAC" , "Right Playback", ES8323_DACCONTROL38, 6, 1),
 SND_SOC_DAPM_PGA("Left Out 1" , SND_SOC_NOPM, 5, 0, NULL, 0),
 SND_SOC_DAPM_PGA("Right Out 1", SND_SOC_NOPM, 4, 0, NULL, 0),
 SND_SOC_DAPM_PGA("Left Out 2" , SND_SOC_NOPM, 3, 0, NULL, 0),
 SND_SOC_DAPM_PGA("Right Out 2" , SND_SOC_NOPM, 2, 0, NULL, 0),

 SND_SOC_DAPM_OUTPUT("LOUT1"),
 SND_SOC_DAPM_OUTPUT("ROUT1"),
 SND_SOC_DAPM_OUTPUT("LOUT2"),
 SND_SOC_DAPM_OUTPUT("ROUT2"),
 SND_SOC_DAPM_OUTPUT("VREF"),


#if 1
 //--------------------------------------------
 // ADC Part
 //--------------------------------------------
 SND_SOC_DAPM_MUX("Differential Left Mux", SND_SOC_NOPM, 0, 0, &es8323_left_diffmux_controls),
 SND_SOC_DAPM_MUX("Differential Right Mux", SND_SOC_NOPM, 0, 0, &es8323_right_diffmux_controls),

 SND_SOC_DAPM_MUX("Left ADC Mux", SND_SOC_NOPM, 0, 0, &es8323_monomux_controls),
 SND_SOC_DAPM_MUX("Right ADC Mux", SND_SOC_NOPM, 0, 0, &es8323_monomux_controls),

    SND_SOC_DAPM_PGA("Left Analog Input" , 0x37/*ES8323_ADCPOWER*/, 7, 1, NULL, 0),
    SND_SOC_DAPM_PGA("Right Analog Input", 0x37/*ES8323_ADCPOWER*/, 6, 1, NULL, 0),
    SND_SOC_DAPM_ADC("Left ADC" , "Left Capture" , 0x37/*ES8323_ADCPOWER*/, 5, 1),
    SND_SOC_DAPM_ADC("Right ADC", "Right Capture", 0x37/*ES8323_ADCPOWER*/, 4, 1),

    SND_SOC_DAPM_MICBIAS("Mic Bias", 0x37/*ES8323_ADCPOWER*/, 3, 1),
#endif

 SND_SOC_DAPM_INPUT("MICIN"),
 SND_SOC_DAPM_INPUT("LINPUT1"),
 SND_SOC_DAPM_INPUT("LINPUT2"),
 SND_SOC_DAPM_INPUT("RINPUT1"),
 SND_SOC_DAPM_INPUT("RINPUT2"),
};
