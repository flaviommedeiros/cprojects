if (parity != PARITY_NONE &&
	    parity != PARITY_CRC16_PR0 &&
	    parity != PARITY_CRC16_PR1 &&
#ifdef __HD64570_H
	    parity != PARITY_CRC16_PR0_CCITT &&
#else
	    parity != PARITY_CRC32_PR1_CCITT &&
#endif
	    parity != PARITY_CRC16_PR1_CCITT)
		return -EINVAL;
