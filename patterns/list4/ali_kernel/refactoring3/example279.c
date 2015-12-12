switch(PhyMode)
	{
		case PHY_11A:
#ifdef DOT11_N_SUPPORT
		case PHY_11AN_MIXED:
#endif // DOT11_N_SUPPORT //
			*pChType = BAND_5G;
			break;
		case PHY_11ABG_MIXED:
#ifdef DOT11_N_SUPPORT
		case PHY_11AGN_MIXED:
		case PHY_11ABGN_MIXED:
#endif // DOT11_N_SUPPORT //
			*pChType = BAND_BOTH;
			break;

		default:
			*pChType = BAND_24G;
			break;
	}
