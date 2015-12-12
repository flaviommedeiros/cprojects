if (0 == phtpriv->beamform_cap 
#ifdef CONFIG_80211AC_VHT
		&& 0 == pvhtpriv->beamform_cap
#endif
		) {
		DBG_871X("The configuration disabled Beamforming! Skip...\n");
		return _FALSE;
	}
