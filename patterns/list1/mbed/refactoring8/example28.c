static const PinMap PinMap_ADC[] = {
    {p1, ADC0_0, 4},
    {p2, ADC0_0, 8},
    {p3, ADC0_0, 16},
    {p4, ADC0_0, 32},
    {p5, ADC0_0, 64},
    {p6, ADC0_0, 128},
#ifndef TARGET_NRF51_DONGLE
    {p26, ADC0_0, 1},
    {p27, ADC0_0, 2},
#endif
    {NC, NC, 0}
};
