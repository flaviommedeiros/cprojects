static const PinMap PinMap_DAC[] = {
#ifdef TARGET_LPC4337
    {P4_3, DAC_0, 0},
#else
    {P4_4, DAC_0, 0},
#endif
    {NC,   NC,    0}
};
