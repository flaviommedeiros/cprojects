static analog_t analog_regs[ANALOG_COUNT] = {
    {"SAR_ADC",             P_SAR_ADC_REG3,       1 << 28, (1 << 30) | (1 << 21),    0,  1},
#ifdef ADJUST_CORE_VOLTAGE
    {"LED_PWM_REG0",        P_LED_PWM_REG0,       1 << 13,          1 << 12,              0,  0}, // needed for core voltage adjustment, so not off
#else
    {"LED_PWM_REG0",        P_LED_PWM_REG0,       1 << 13,          1 << 12,              0,  1},
#endif
    //{"VGHL_PWM_REG0",       P_VGHL_PWM_REG0,      1 << 13,          1 << 12,              0,  1},
};
