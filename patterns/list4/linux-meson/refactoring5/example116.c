#ifdef CONFIG_80211AC_VHT
if (IsSupportedVHT(psta->wireless_mode))
								STBC_TX = TEST_FLAG(psta->vhtpriv.stbc_cap, STBC_VHT_ENABLE_TX);
							else
#endif
								STBC_TX = TEST_FLAG(psta->htpriv.stbc_cap, STBC_HT_ENABLE_TX);
