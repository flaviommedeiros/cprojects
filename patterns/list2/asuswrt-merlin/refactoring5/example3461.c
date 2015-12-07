#ifdef TO_DO_LIST
if (Adapter->bInHctTest)
		{
		    regBwOpMode = BW_OPMODE_20MHZ;
		    regRATR = RATE_ALL_CCK | RATE_ALL_OFDM_AG;
		    regRRSR = RATE_ALL_CCK | RATE_ALL_OFDM_AG;
		}
		else
#endif
		{
		    regBwOpMode = BW_OPMODE_20MHZ;
		    regRATR = RATE_ALL_CCK | RATE_ALL_OFDM_AG | RATE_ALL_OFDM_1SS | RATE_ALL_OFDM_2SS;
		    regRRSR = RATE_ALL_CCK | RATE_ALL_OFDM_AG;
		}
