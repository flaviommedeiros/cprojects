#ifdef WL_BEAMFORMING
if (PPR_TXBF_ENAB()) {
				offset = mcs_groups_nss2_txbf[tx_chains - Nss][mode];
			} else
#endif /* WL_BEAMFORMING */
			{
				offset = mcs_groups_nss2[tx_chains - Nss][mode];
			}
