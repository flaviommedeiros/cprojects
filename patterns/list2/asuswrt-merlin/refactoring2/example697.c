#ifdef RTMP_MAC_USB
if (!IS_RT3572(pAd))
#endif /* RTMP_MAC_USB // */
		{
			RT30xxReadRFRegister(pAd, RF_R27, &RFValue);
			RFValue |= 0x77;
			RT30xxWriteRFRegister(pAd, RF_R27, RFValue);
		}
