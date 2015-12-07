#ifdef WL_BEAMFORMING
if (mode == WL_TX_MODE_TXBF)
			group_pwrs = bw_pwrs->p_1x3txbf_ofdm;
		else
#endif
			group_pwrs = bw_pwrs->p_1x3cdd_ofdm;
