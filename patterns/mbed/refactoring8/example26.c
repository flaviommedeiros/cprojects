const uint32_t pinmapping[] = {
#if (SAMD20E | SAMD21E)
        PIN_PA02B_ADC_AIN0,  PIN_PA03B_ADC_AIN1,
        PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
        PIN_PA04B_ADC_AIN4,  PIN_PA05B_ADC_AIN5,
        PIN_PA06B_ADC_AIN6,  PIN_PA07B_ADC_AIN7,
        PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
        PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
        PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
        PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
        PIN_PA08B_ADC_AIN16, PIN_PA09B_ADC_AIN17,
        PIN_PA10B_ADC_AIN18, PIN_PA11B_ADC_AIN19,
#elif (SAMD20G | SAMD21G)
        PIN_PA02B_ADC_AIN0,  PIN_PA03B_ADC_AIN1,
        PIN_PB08B_ADC_AIN2,  PIN_PB09B_ADC_AIN3,
        PIN_PA04B_ADC_AIN4,  PIN_PA05B_ADC_AIN5,
        PIN_PA06B_ADC_AIN6,  PIN_PA07B_ADC_AIN7,
        PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
        PIN_PB02B_ADC_AIN10, PIN_PB03B_ADC_AIN11,
        PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
        PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
        PIN_PA08B_ADC_AIN16, PIN_PA09B_ADC_AIN17,
        PIN_PA10B_ADC_AIN18, PIN_PA11B_ADC_AIN19,
#elif (SAMD20J | SAMD21J)
        PIN_PA02B_ADC_AIN0,  PIN_PA03B_ADC_AIN1,
        PIN_PB08B_ADC_AIN2,  PIN_PB09B_ADC_AIN3,
        PIN_PA04B_ADC_AIN4,  PIN_PA05B_ADC_AIN5,
        PIN_PA06B_ADC_AIN6,  PIN_PA07B_ADC_AIN7,
        PIN_PB00B_ADC_AIN8,  PIN_PB01B_ADC_AIN9,
        PIN_PB02B_ADC_AIN10, PIN_PB03B_ADC_AIN11,
        PIN_PB04B_ADC_AIN12, PIN_PB05B_ADC_AIN13,
        PIN_PB06B_ADC_AIN14, PIN_PB07B_ADC_AIN15,
        PIN_PA08B_ADC_AIN16, PIN_PA09B_ADC_AIN17,
        PIN_PA10B_ADC_AIN18, PIN_PA11B_ADC_AIN19,
#elif SAMR21E
        PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
        PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
        PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
        PIN_PA06B_ADC_AIN6,  PIN_PA07B_ADC_AIN7,
        PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
        PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
        PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
        PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
        PIN_PA08B_ADC_AIN16, PIN_PA09B_ADC_AIN17,
        PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
#elif SAMR21G
        PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
        PIN_PB08B_ADC_AIN2,  PIN_PB09B_ADC_AIN3,
        PIN_PA04B_ADC_AIN4,  PIN_PA05B_ADC_AIN5,
        PIN_PA06B_ADC_AIN6,  PIN_PA07B_ADC_AIN7,
        PIN_PB00B_ADC_AIN8,  PIN_INVALID_ADC_AIN,
        PIN_PB02B_ADC_AIN10, PIN_PB03B_ADC_AIN11,
        PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
        PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
        PIN_PA08B_ADC_AIN16, PIN_PA09B_ADC_AIN17,
        PIN_PA10B_ADC_AIN18, PIN_PA11B_ADC_AIN19,
#elif (SAMD10C | SAMD11C)
        PIN_PA02B_ADC_AIN0,  PIN_INVALID_ADC_AIN,
        PIN_PA04B_ADC_AIN2,  PIN_PA05B_ADC_AIN3,
        PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
        PIN_PA14B_ADC_AIN6,  PIN_PA15B_ADC_AIN7,
        PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
        PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
        PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
        PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
        PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
        PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
#elif (SAMD10DS | SAMD11DS)
        PIN_PA02B_ADC_AIN0,  PIN_INVALID_ADC_AIN,
        PIN_PA04B_ADC_AIN2,  PIN_PA05B_ADC_AIN3,
        PIN_PA06B_ADC_AIN4,  PIN_PA07B_ADC_AIN5,
        PIN_PA14B_ADC_AIN6,  PIN_PA15B_ADC_AIN7,
        PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
        PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
        PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
        PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
        PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
        PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
#elif (SAMD10DM | SAMD11DM)
        PIN_PA02B_ADC_AIN0,  PIN_PA03B_ADC_AIN1,
        PIN_PA04B_ADC_AIN2,  PIN_PA05B_ADC_AIN3,
        PIN_PA06B_ADC_AIN4,  PIN_PA07B_ADC_AIN5,
        PIN_PA14B_ADC_AIN6,  PIN_PA15B_ADC_AIN7,
        PIN_PA10B_ADC_AIN8,  PIN_PA11B_ADC_AIN9,
        PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
        PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
        PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
        PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
        PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
#elif (SAML21E)
        PIN_PA02B_ADC_AIN0,  PIN_PA03B_ADC_AIN1,
        PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
        PIN_PA04B_ADC_AIN4,  PIN_PA05B_ADC_AIN5,
        PIN_PA06B_ADC_AIN6,  PIN_PA07B_ADC_AIN7,
        PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
        PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
        PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
        PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
        PIN_PA08B_ADC_AIN16, PIN_PA09B_ADC_AIN17,
        PIN_PA10B_ADC_AIN18, PIN_PA11B_ADC_AIN19,
        PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
        PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
#elif (SAML21G)
        PIN_PA02B_ADC_AIN0,  PIN_PA03B_ADC_AIN1,
        PIN_PB08B_ADC_AIN2,  PIN_PB09B_ADC_AIN3,
        PIN_PA04B_ADC_AIN4,  PIN_PA05B_ADC_AIN5,
        PIN_PA06B_ADC_AIN6,  PIN_PA07B_ADC_AIN7,
        PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
        PIN_PB02B_ADC_AIN10, PIN_PB03B_ADC_AIN11,
        PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
        PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
        PIN_PA08B_ADC_AIN16, PIN_PA09B_ADC_AIN17,
        PIN_PA10B_ADC_AIN18, PIN_PA11B_ADC_AIN19,
        PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
        PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
#elif (SAML21J)
        PIN_PA02B_ADC_AIN0,  PIN_PA03B_ADC_AIN1,
        PIN_PB08B_ADC_AIN2,  PIN_PB09B_ADC_AIN3,
        PIN_PA04B_ADC_AIN4,  PIN_PA05B_ADC_AIN5,
        PIN_PA06B_ADC_AIN6,  PIN_PA07B_ADC_AIN7,
        PIN_PB00B_ADC_AIN8,  PIN_PB01B_ADC_AIN9,
        PIN_PB02B_ADC_AIN10, PIN_PB03B_ADC_AIN11,
        PIN_PB04B_ADC_AIN12, PIN_PB05B_ADC_AIN13,
        PIN_PB06B_ADC_AIN14, PIN_PB07B_ADC_AIN15,
        PIN_PA08B_ADC_AIN16, PIN_PA09B_ADC_AIN17,
        PIN_PA10B_ADC_AIN18, PIN_PA11B_ADC_AIN19,
        PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
        PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
#else
#  error ADC pin mappings are not defined for this device.
#endif
    };
