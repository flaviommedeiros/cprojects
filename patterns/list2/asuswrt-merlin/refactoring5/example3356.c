#ifdef WL_BEAMFORMING
if (PPR_TXBF_ENAB()) {
				offset = mcs_groups_nss3_txbf[mode];
			} else
#endif /* WL_BEAMFORMING */
			{
				offset = mcs_groups_nss3[mode];
			}
