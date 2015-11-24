uint32_t sercom_address[6] = {
#if (SAMD21) || (SAMR21)
        0x42000800UL,  // Base address of SERCOM0
        0x42000C00UL,  // Base address of SERCOM1
        0x42001000UL,  // Base address of SERCOM2
        0x42001400UL,  // Base address of SERCOM3
        0x42001800UL,  // Base address of SERCOM4
        0x42001C00UL   // Base address of SERCOM5
#elif (SAML21)
        0x42000000UL,  // Base address of SERCOM0
        0x42000400UL,  // Base address of SERCOM1
        0x42000800UL,  // Base address of SERCOM2
        0x42000C00UL,  // Base address of SERCOM3
        0x42001000UL,  // Base address of SERCOM4
        0x43000400UL   // Base address of SERCOM5
#endif
    };
