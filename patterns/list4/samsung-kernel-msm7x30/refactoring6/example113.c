if ((staIsHT) 
#ifdef ANI_LITTLE_BYTE_ENDIAN
            &&( (rxRSNIe.pwise_cipher_suites[i][3] & SECURITY_SUITE_TYPE_MASK) == SECURITY_SUITE_TYPE_CCMP))
#else
            &&( (rxRSNIe.pwise_cipher_suites[i][0] & SECURITY_SUITE_TYPE_MASK) == SECURITY_SUITE_TYPE_CCMP)
