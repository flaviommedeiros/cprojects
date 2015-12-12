#ifdef CONFIG_80211AC_VHT
if (psta->vhtpriv.vht_option) {
		if(TEST_FLAG(psta->vhtpriv.ldpc_cap, LDPC_VHT_ENABLE_TX))
			psta->ldpc = 1;

		if(TEST_FLAG(psta->vhtpriv.stbc_cap, STBC_VHT_ENABLE_TX))
			psta->stbc = 1;
	}
	else
#endif //CONFIG_80211AC_VHT
	if (psta->htpriv.ht_option) {
		if(TEST_FLAG(psta->htpriv.ldpc_cap, LDPC_HT_ENABLE_TX))
			psta->ldpc = 1;

		if(TEST_FLAG(psta->htpriv.stbc_cap, STBC_HT_ENABLE_TX))
			psta->stbc = 1;
	} else {
		psta->ldpc = 0;
		psta->stbc = 0;
	}
