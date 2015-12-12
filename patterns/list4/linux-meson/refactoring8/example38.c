static const struct snd_soc_dapm_route intercon[] = {
 /* left mixer */
 {"Left Mixer", "Left Playback Switch" , "Left DAC"},

 /* right mixer */
 {"Right Mixer", "Right Playback Switch" , "Right DAC"},

 /* left out 1 */
 {"Left Out 1" , NULL, "Left Mixer"},
 {"LOUT1" , NULL, "Left Out 1"},

 /* right out 1 */
 {"Right Out 1", NULL, "Right Mixer"},
 {"ROUT1" , NULL, "Right Out 1"},

 /* left out 2 */
 {"Left Out 2" , NULL, "Left Mixer"},
 {"LOUT2" , NULL, "Left Out 2"},

 /* right out 2 */
 {"Right Out 2", NULL, "Right Mixer"},
 {"ROUT2" , NULL, "Right Out 2"},


#if 1
 /* Differential Mux */
 {"Differential Left Mux" , "Line 1", "LINPUT1"},
 {"Differential Right Mux", "Line 1", "RINPUT1"},
 {"Differential Left Mux" , "Line 2", "LINPUT2"},
 {"Differential Right Mux", "Line 2", "RINPUT2"},

 /* Left Line Mux */
 {"Left Line Mux", "Line 1" , "LINPUT1"},
 {"Left Line Mux", "Line 2" , "LINPUT2"},
 {"Left Line Mux", "Differential", "Differential Left Mux"},

 /* Right Line Mux */
 {"Right Line Mux", "Line 1" , "RINPUT1"},
 {"Right Line Mux", "Line 2" , "RINPUT2"},
 {"Right Line Mux", "Differential", "Differential Right Mux"},

 /* Left ADC Mux */
 {"Left ADC Mux", "Stereo" , "Left Line Mux"},
// {"Left ADC Mux", "Mono (Left)" , "Left Line Mux"},

 /* Right ADC Mux */
 {"Right ADC Mux", "Stereo" , "Right Line Mux"},
// {"Right ADC Mux", "Mono (Right)", "Right Line Mux"},

 /* ADC */
 {"Left ADC" , NULL, "Left ADC Mux"},
 {"Right ADC", NULL, "Right ADC Mux"},


 {"Left ADC" , NULL, "Mic Bias"},
 {"Right ADC", NULL, "Mic Bias"},

 {"Mic Bias", NULL, "MICIN"},
#endif
};
