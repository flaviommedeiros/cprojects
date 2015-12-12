static const struct snd_soc_dapm_route rt5616_dapm_routes[] = {
    {"IN1P", NULL, "LDO"},
    {"IN2P", NULL, "LDO"},

    {"IN1P", NULL, "MIC1"},
    {"IN2P", NULL, "MIC2"},
    {"IN2N", NULL, "MIC2"},

    {"BST1", NULL, "IN1P"},
    {"BST2", NULL, "IN2P"},
    {"BST2", NULL, "IN2N"},
#ifdef POWER_ON_MICBIAS1
    {"BST1", NULL, "micbias1"},
    {"BST2", NULL, "micbias1"},
#endif

    {"INL1 VOL", NULL, "IN2P"},
    {"INR1 VOL", NULL, "IN2N"},

    {"RECMIXL", "INL1 Switch", "INL1 VOL"},
    {"RECMIXL", "BST2 Switch", "BST2"},
    {"RECMIXL", "BST1 Switch", "BST1"},

    {"RECMIXR", "INR1 Switch", "INR1 VOL"},
    {"RECMIXR", "BST2 Switch", "BST2"},
    {"RECMIXR", "BST1 Switch", "BST1"},

    {"ADC L", NULL, "RECMIXL"},
    {"ADC R", NULL, "RECMIXR"},

    {"Stereo1 ADC MIXL", "ADC1 Switch", "ADC L"},
    {"Stereo1 ADC MIXL", NULL, "stereo1 filter"},
    {"stereo1 filter", NULL, "PLL1", check_sysclk1_source},

    {"Stereo1 ADC MIXR", "ADC1 Switch", "ADC R"},
    {"Stereo1 ADC MIXR", NULL, "stereo1 filter"},
    {"stereo1 filter", NULL, "PLL1", check_sysclk1_source},

    {"IF1 ADC1", NULL, "Stereo1 ADC MIXL"},
    {"IF1 ADC1", NULL, "Stereo1 ADC MIXR"},
    {"IF1 ADC1", NULL, "I2S1"},

    {"AIF1TX", NULL, "IF1 ADC1"},

    {"IF1 DAC", NULL, "AIF1RX"},
    {"IF1 DAC", NULL, "I2S1"},

    {"IF1 DAC1 L", NULL, "IF1 DAC"},
    {"IF1 DAC1 R", NULL, "IF1 DAC"},

    {"DAC MIXL", "Stereo ADC Switch", "Stereo1 ADC MIXL"},
    {"DAC MIXL", "INF1 Switch", "IF1 DAC1 L"},
    {"DAC MIXR", "Stereo ADC Switch", "Stereo1 ADC MIXR"},
    {"DAC MIXR", "INF1 Switch", "IF1 DAC1 R"},

    {"Audio DSP", NULL, "DAC MIXL"},
    {"Audio DSP", NULL, "DAC MIXR"},

    {"Stereo DAC MIXL", "DAC L1 Switch", "Audio DSP"},
    {"Stereo DAC MIXL", "DAC R1 Switch", "DAC MIXR"},
    {"Stereo DAC MIXL", NULL, "Stero1 DAC Power"},
    {"Stereo DAC MIXR", "DAC R1 Switch", "Audio DSP"},
    {"Stereo DAC MIXR", "DAC L1 Switch", "DAC MIXL"},
    {"Stereo DAC MIXR", NULL, "Stero1 DAC Power"},

    {"DAC L1", NULL, "Stereo DAC MIXL"},
    {"DAC L1", NULL, "PLL1", check_sysclk1_source},
    {"DAC R1", NULL, "Stereo DAC MIXR"},
    {"DAC R1", NULL, "PLL1", check_sysclk1_source},

    {"OUT MIXL", "BST1 Switch", "BST1"},
    {"OUT MIXL", "BST2 Switch", "BST2"},
    {"OUT MIXL", "INL1 Switch", "INL1 VOL"},
    {"OUT MIXL", "REC MIXL Switch", "RECMIXL"},
    {"OUT MIXL", "DAC L1 Switch", "DAC L1"},

    {"OUT MIXR", "BST2 Switch", "BST2"},
    {"OUT MIXR", "BST1 Switch", "BST1"},
    {"OUT MIXR", "INR1 Switch", "INR1 VOL"},
    {"OUT MIXR", "REC MIXR Switch", "RECMIXR"},
    {"OUT MIXR", "DAC R1 Switch", "DAC R1"},

    {"HPOVOL L", NULL, "OUT MIXL"},
    {"HPOVOL R", NULL, "OUT MIXR"},
    {"OUTVOL L", NULL, "OUT MIXL"},
    {"OUTVOL R", NULL, "OUT MIXR"},

    {"DAC 1", NULL, "DAC L1"},
    {"DAC 1", NULL, "DAC R1"},
    {"HPOVOL", NULL, "HPOVOL L"},
    {"HPOVOL", NULL, "HPOVOL R"},
    {"HPO MIX", "DAC1 Switch", "DAC 1"},
    {"HPO MIX", "HPVOL Switch", "HPOVOL"},

    {"LOUT MIX", "DAC L1 Switch", "DAC L1"},
    {"LOUT MIX", "DAC R1 Switch", "DAC R1"},
    {"LOUT MIX", "OUTVOL L Switch", "OUTVOL L"},
    {"LOUT MIX", "OUTVOL R Switch", "OUTVOL R"},

    {"HP amp", NULL, "HPO MIX"},
    {"HPOL", NULL, "HP amp"},
    {"HPOR", NULL, "HP amp"},

    {"LOUT amp", NULL, "LOUT MIX"},
    {"LOUTL", NULL, "LOUT amp"},
    {"LOUTR", NULL, "LOUT amp"},

};
