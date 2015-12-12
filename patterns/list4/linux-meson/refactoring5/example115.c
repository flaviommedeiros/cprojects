#ifdef CONFIG_80211N_HT
if (pDM_Odm->SupportICType == ODM_RTL8192E || pDM_Odm->SupportICType == ODM_RTL8812) {
#ifdef CONFIG_BEAMFORMING
						BEAMFORMING_CAP Beamform_cap = beamforming_get_entry_beam_cap_by_mac_id(&Adapter->mlmepriv, psta->mac_id);

						if (Beamform_cap & (BEAMFORMER_CAP_HT_EXPLICIT | BEAMFORMER_CAP_VHT_SU))
							TxBF_EN = 1;
						else
							TxBF_EN = 0;

						if (TxBF_EN)
							STBC_TX = 0;
						else
#endif
						{
#ifdef CONFIG_80211AC_VHT
							if (IsSupportedVHT(psta->wireless_mode))
								STBC_TX = TEST_FLAG(psta->vhtpriv.stbc_cap, STBC_VHT_ENABLE_TX);
							else
#endif
								STBC_TX = TEST_FLAG(psta->htpriv.stbc_cap, STBC_HT_ENABLE_TX);
						}
					}
