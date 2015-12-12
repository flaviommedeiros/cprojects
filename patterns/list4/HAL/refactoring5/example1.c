#ifdef __LONG_64__
if (bit >= 0x0000000100000000UL) {
                if (bit >= 0x0001000000000000UL) {
                    bitIndex = 48;
                } else {
                    bitIndex = 32;
                }
            } else 
#endif /* __LONG_64__ */
            if (bit >= 0x00010000UL) {
                bitIndex = 16;
            }
