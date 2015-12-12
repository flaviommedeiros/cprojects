static const struct snd_soc_dapm_widget rt5616_dapm_widgets[] = {
    SND_SOC_DAPM_SUPPLY("PLL1", RT5616_PWR_ANLG2,
            RT5616_PWR_PLL_BIT, 0, NULL, 0),
    /* Input Side */
    /* micbias */
    SND_SOC_DAPM_SUPPLY("LDO", RT5616_PWR_ANLG1,
            RT5616_PWR_LDO_BIT, 0, NULL, 0),
#ifdef POWER_ON_MICBIAS1
//  SND_SOC_DAPM_SUPPLY("micbias1", RT5616_PWR_ANLG2,
//          RT5616_PWR_MB1_BIT, 0, NULL, 0),
    SND_SOC_DAPM_SUPPLY("micbias1", SND_SOC_NOPM,
            RT5616_PWR_MB1_BIT, 0, mic_bias_event, 0),
  
#else
    SND_SOC_DAPM_MICBIAS("micbias1", RT5616_PWR_ANLG2,
            RT5616_PWR_MB1_BIT, 0),
#endif
    /* Input Lines */
    SND_SOC_DAPM_INPUT("MIC1"),
    SND_SOC_DAPM_INPUT("MIC2"),


    SND_SOC_DAPM_INPUT("IN1P"),
    SND_SOC_DAPM_INPUT("IN2P"),
    SND_SOC_DAPM_INPUT("IN2N"),

    /* Boost */
    SND_SOC_DAPM_PGA_E("BST1", RT5616_PWR_ANLG2,
        RT5616_PWR_BST1_BIT, 0, NULL, 0, rt5616_bst1_event,
        SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMU),
    SND_SOC_DAPM_PGA_E("BST2", RT5616_PWR_ANLG2,
        RT5616_PWR_BST2_BIT, 0, NULL, 0, rt5616_bst2_event,
        SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMU),
    /* Input Volume */
    SND_SOC_DAPM_PGA("INL1 VOL", RT5616_PWR_VOL,
        RT5616_PWR_IN1_L_BIT, 0, NULL, 0),
    SND_SOC_DAPM_PGA("INR1 VOL", RT5616_PWR_VOL,
        RT5616_PWR_IN1_R_BIT, 0, NULL, 0),
    SND_SOC_DAPM_PGA("INL2 VOL", RT5616_PWR_VOL,
        RT5616_PWR_IN2_L_BIT, 0, NULL, 0),
    SND_SOC_DAPM_PGA("INR2 VOL", RT5616_PWR_VOL,
        RT5616_PWR_IN2_R_BIT, 0, NULL, 0),

    /* REC Mixer */
    SND_SOC_DAPM_MIXER("RECMIXL", RT5616_PWR_MIXER, RT5616_PWR_RM_L_BIT, 0,
            rt5616_rec_l_mix, ARRAY_SIZE(rt5616_rec_l_mix)),
    SND_SOC_DAPM_MIXER("RECMIXR", RT5616_PWR_MIXER, RT5616_PWR_RM_R_BIT, 0,
            rt5616_rec_r_mix, ARRAY_SIZE(rt5616_rec_r_mix)),
    /* ADCs */
    SND_SOC_DAPM_ADC_E("ADC L", NULL, RT5616_PWR_DIG1,
        RT5616_PWR_ADC_L_BIT, 0, rt5616_adc_event,
        SND_SOC_DAPM_POST_PMD | SND_SOC_DAPM_POST_PMU),
    SND_SOC_DAPM_ADC_E("ADC R", NULL, RT5616_PWR_DIG1,
        RT5616_PWR_ADC_R_BIT, 0, rt5616_adc_event,
        SND_SOC_DAPM_POST_PMD | SND_SOC_DAPM_POST_PMU),

    /* ADC Mixer */
    SND_SOC_DAPM_SUPPLY("stereo1 filter", RT5616_PWR_DIG2,
        RT5616_PWR_ADC_STO1_F_BIT, 0, NULL, 0),
    SND_SOC_DAPM_MIXER("Stereo1 ADC MIXL", SND_SOC_NOPM, 0, 0,
        rt5616_sto1_adc_l_mix, ARRAY_SIZE(rt5616_sto1_adc_l_mix)),
    SND_SOC_DAPM_MIXER("Stereo1 ADC MIXR", SND_SOC_NOPM, 0, 0,
        rt5616_sto1_adc_r_mix, ARRAY_SIZE(rt5616_sto1_adc_r_mix)),

    /* Digital Interface */
    SND_SOC_DAPM_SUPPLY("I2S1", RT5616_PWR_DIG1,
        RT5616_PWR_I2S1_BIT, 0, NULL, 0),
    SND_SOC_DAPM_PGA("IF1 DAC", SND_SOC_NOPM, 0, 0, NULL, 0),
    SND_SOC_DAPM_PGA("IF1 DAC1 L", SND_SOC_NOPM, 0, 0, NULL, 0),
    SND_SOC_DAPM_PGA("IF1 DAC1 R", SND_SOC_NOPM, 0, 0, NULL, 0),
    SND_SOC_DAPM_PGA("IF1 ADC1", SND_SOC_NOPM, 0, 0, NULL, 0),

    /* Digital Interface Select */

    /* Audio Interface */
    SND_SOC_DAPM_AIF_IN("AIF1RX", "AIF1 Playback", 0, SND_SOC_NOPM, 0, 0),
    SND_SOC_DAPM_AIF_OUT("AIF1TX", "AIF1 Capture", 0, SND_SOC_NOPM, 0, 0),

    /* Audio DSP */
    SND_SOC_DAPM_PGA("Audio DSP", SND_SOC_NOPM, 0, 0, NULL, 0),

    /* Output Side */
    /* DAC mixer before sound effect  */
    SND_SOC_DAPM_MIXER("DAC MIXL", SND_SOC_NOPM, 0, 0,
        rt5616_dac_l_mix, ARRAY_SIZE(rt5616_dac_l_mix)),
    SND_SOC_DAPM_MIXER("DAC MIXR", SND_SOC_NOPM, 0, 0,
        rt5616_dac_r_mix, ARRAY_SIZE(rt5616_dac_r_mix)),

    SND_SOC_DAPM_SUPPLY("Stero1 DAC Power", RT5616_PWR_DIG2,
            RT5616_PWR_DAC_STO1_F_BIT, 0, NULL, 0),

    /* DAC Mixer */
    SND_SOC_DAPM_MIXER("Stereo DAC MIXL", SND_SOC_NOPM, 0, 0,
        rt5616_sto_dac_l_mix, ARRAY_SIZE(rt5616_sto_dac_l_mix)),
    SND_SOC_DAPM_MIXER("Stereo DAC MIXR", SND_SOC_NOPM, 0, 0,
        rt5616_sto_dac_r_mix, ARRAY_SIZE(rt5616_sto_dac_r_mix)),

    /* DACs */
    SND_SOC_DAPM_DAC("DAC L1", NULL, RT5616_PWR_DIG1,
            RT5616_PWR_DAC_L1_BIT, 0),
    SND_SOC_DAPM_DAC("DAC R1", NULL, RT5616_PWR_DIG1,
            RT5616_PWR_DAC_R1_BIT, 0),
    /* OUT Mixer */
    SND_SOC_DAPM_MIXER("OUT MIXL", RT5616_PWR_MIXER, RT5616_PWR_OM_L_BIT,
        0, rt5616_out_l_mix, ARRAY_SIZE(rt5616_out_l_mix)),
    SND_SOC_DAPM_MIXER("OUT MIXR", RT5616_PWR_MIXER, RT5616_PWR_OM_R_BIT,
        0, rt5616_out_r_mix, ARRAY_SIZE(rt5616_out_r_mix)),
    /* Ouput Volume */
    SND_SOC_DAPM_PGA("OUTVOL L", RT5616_PWR_VOL,
        RT5616_PWR_OV_L_BIT, 0, NULL, 0),
    SND_SOC_DAPM_PGA("OUTVOL R", RT5616_PWR_VOL,
        RT5616_PWR_OV_R_BIT, 0, NULL, 0),
    SND_SOC_DAPM_PGA("HPOVOL L", RT5616_PWR_VOL,
        RT5616_PWR_HV_L_BIT, 0, NULL, 0),
    SND_SOC_DAPM_PGA("HPOVOL R", RT5616_PWR_VOL,
        RT5616_PWR_HV_R_BIT, 0, NULL, 0),
    SND_SOC_DAPM_PGA("DAC 1", SND_SOC_NOPM,
        0, 0, NULL, 0),
    SND_SOC_DAPM_PGA("DAC 2", SND_SOC_NOPM,
        0, 0, NULL, 0),
    SND_SOC_DAPM_PGA("HPOVOL", SND_SOC_NOPM,
        0, 0, NULL, 0),
    SND_SOC_DAPM_PGA("INL1", RT5616_PWR_VOL,
        RT5616_PWR_IN1_L_BIT, 0, NULL, 0),
    SND_SOC_DAPM_PGA("INR1", RT5616_PWR_VOL,
        RT5616_PWR_IN1_R_BIT, 0, NULL, 0),
    SND_SOC_DAPM_PGA("INL2", RT5616_PWR_VOL,
        RT5616_PWR_IN2_L_BIT, 0, NULL, 0),
    SND_SOC_DAPM_PGA("INR2", RT5616_PWR_VOL,
        RT5616_PWR_IN2_R_BIT, 0, NULL, 0),
    /* HPO/LOUT/Mono Mixer */
    SND_SOC_DAPM_MIXER("HPO MIX", SND_SOC_NOPM, 0, 0,
        rt5616_hpo_mix, ARRAY_SIZE(rt5616_hpo_mix)),
    SND_SOC_DAPM_MIXER("LOUT MIX", SND_SOC_NOPM, 0, 0,
        rt5616_lout_mix, ARRAY_SIZE(rt5616_lout_mix)),

    SND_SOC_DAPM_PGA_S("HP amp", 1, SND_SOC_NOPM, 0, 0,
        rt5616_hp_event, SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMU),
    SND_SOC_DAPM_PGA_S("LOUT amp", 1, SND_SOC_NOPM, 0, 0,
        rt5616_lout_event, SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMU),

    /* Output Lines */
    SND_SOC_DAPM_OUTPUT("HPOL"),
    SND_SOC_DAPM_OUTPUT("HPOR"),
    SND_SOC_DAPM_OUTPUT("LOUTL"),
    SND_SOC_DAPM_OUTPUT("LOUTR"),
};
