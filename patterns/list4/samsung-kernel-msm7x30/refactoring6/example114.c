if ((staIsHT) 
#ifdef ANI_LITTLE_BYTE_ENDIAN
            &&( (rxWPAIe.unicast_ciphers[i][3] & SECURITY_SUITE_TYPE_MASK) == SECURITY_SUITE_TYPE_CCMP))
#else
            &&( (rxWPAIe.unicast_ciphers[i][0] & SECURITY_SUITE_TYPE_MASK) == SECURITY_SUITE_TYPE_CCMP)
