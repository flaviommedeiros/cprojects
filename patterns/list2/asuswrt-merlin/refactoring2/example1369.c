#ifdef RTMP_MAC_USB
if (!IS_RT3572(pAd))
#endif /* RTMP_MAC_USB // */
	{
		/* RF_BLOCK_en. RF R1 register Bit 0 to 0 */
		RT30xxReadRFRegister(pAd, RF_R01, &RFValue);
		RFValue &= (~0x01);
		RT30xxWriteRFRegister(pAd, RF_R01, RFValue);

		/* VCO_IC, RF R7 register Bit 4 & Bit 5 to 0 */
		RT30xxReadRFRegister(pAd, RF_R07, &RFValue);
		RFValue &= (~0x30);
		RT30xxWriteRFRegister(pAd, RF_R07, RFValue);

		/* Idoh, RF R9 register Bit 1, Bit 2 & Bit 3 to 0 */
		RT30xxReadRFRegister(pAd, RF_R09, &RFValue);
		RFValue &= (~0x0E);
		RT30xxWriteRFRegister(pAd, RF_R09, RFValue);

		/* RX_CTB_en, RF R21 register Bit 7 to 0 */
		RT30xxReadRFRegister(pAd, RF_R21, &RFValue);
		RFValue &= (~0x80);
		RT30xxWriteRFRegister(pAd, RF_R21, RFValue);
	}
