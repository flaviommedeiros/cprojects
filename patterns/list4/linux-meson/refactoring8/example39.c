static const struct snd_kcontrol_new wm8960_snd_controls[] = {
SOC_DOUBLE_R_TLV("Capture Volume", WM8960_LINVOL, WM8960_RINVOL,
         0, 63, 0, adc_tlv),
SOC_DOUBLE_R("Capture Volume ZC Switch", WM8960_LINVOL, WM8960_RINVOL,
    6, 1, 0),
SOC_DOUBLE_R("Capture Switch", WM8960_LINVOL, WM8960_RINVOL,
    7, 1, 0),

SOC_DOUBLE_R_TLV("Playback Volume", WM8960_LDAC, WM8960_RDAC,
         0, 255, 0, dac_tlv),

SOC_DOUBLE_R_TLV("Headphone Playback Volume", WM8960_LOUT1, WM8960_ROUT1,
         0, 127, 0, out_tlv),
SOC_DOUBLE_R("Headphone Playback ZC Switch", WM8960_LOUT1, WM8960_ROUT1,
    7, 1, 0),

SOC_DOUBLE_R_TLV("Speaker Playback Volume", WM8960_LOUT2, WM8960_ROUT2,
         0, 127, 0, out_tlv),
SOC_DOUBLE_R("Speaker Playback ZC Switch", WM8960_LOUT2, WM8960_ROUT2,
    7, 1, 0),
SOC_SINGLE("Speaker DC Volume", WM8960_CLASSD3, 3, 5, 0),
SOC_SINGLE("Speaker AC Volume", WM8960_CLASSD3, 0, 5, 0),

SOC_SINGLE("PCM Playback -6dB Switch", WM8960_DACCTL1, 7, 1, 0),
SOC_ENUM("ADC Polarity", wm8960_enum[0]),
SOC_SINGLE("ADC High Pass Filter Switch", WM8960_DACCTL1, 0, 1, 0),

SOC_ENUM("DAC Polarity", wm8960_enum[2]),
SOC_SINGLE_BOOL_EXT("DAC Deemphasis Switch", 0,
            wm8960_get_deemph, wm8960_put_deemph),

SOC_ENUM("3D Filter Upper Cut-Off", wm8960_enum[2]),
SOC_ENUM("3D Filter Lower Cut-Off", wm8960_enum[3]),
SOC_SINGLE("3D Volume", WM8960_3D, 1, 15, 0),
SOC_SINGLE("3D Switch", WM8960_3D, 0, 1, 0),

SOC_ENUM("ALC Function", wm8960_enum[4]),
SOC_SINGLE("ALC Max Gain", WM8960_ALC1, 4, 7, 0),
SOC_SINGLE("ALC Target", WM8960_ALC1, 0, 15, 1),
SOC_SINGLE("ALC Min Gain", WM8960_ALC2, 4, 7, 0),
SOC_SINGLE("ALC Hold Time", WM8960_ALC2, 0, 15, 0),
SOC_ENUM("ALC Mode", wm8960_enum[5]),
SOC_SINGLE("ALC Decay", WM8960_ALC3, 4, 15, 0),
SOC_SINGLE("ALC Attack", WM8960_ALC3, 0, 15, 0),

SOC_SINGLE("Noise Gate Threshold", WM8960_NOISEG, 3, 31, 0),
SOC_SINGLE("Noise Gate Switch", WM8960_NOISEG, 0, 1, 0),

#if 0
SOC_DOUBLE_R("ADC PCM Capture Volume", WM8960_LINPATH, WM8960_RINPATH,
    0, 127, 0),
#else
SOC_DOUBLE_R_TLV("ADC PCM Capture Volume", WM8960_LINPATH, WM8960_RINPATH,
    4, 3, 0, input_pag_tlv),
#endif

SOC_SINGLE_TLV("Left Output Mixer Boost Bypass Volume",
           WM8960_BYPASS1, 4, 7, 1, bypass_tlv),
SOC_SINGLE_TLV("Left Output Mixer LINPUT3 Volume",
           WM8960_LOUTMIX, 4, 7, 1, bypass_tlv),
SOC_SINGLE_TLV("Right Output Mixer Boost Bypass Volume",
           WM8960_BYPASS2, 4, 7, 1, bypass_tlv),
SOC_SINGLE_TLV("Right Output Mixer RINPUT3 Volume",
           WM8960_ROUTMIX, 4, 7, 1, bypass_tlv),

SOC_SINGLE("DAC Mono Mix", WM8960_ADDCTL1, 4, 1, 0),

SOC_SINGLE("ADC Output Select", WM8960_ADDCTL1, 2, 3, 0),
};
