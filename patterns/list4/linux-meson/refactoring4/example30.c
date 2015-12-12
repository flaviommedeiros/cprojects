#ifdef CONFIG_IEEE80211W
if (value <= _BIP_)
#else
	if (value <= _WEP_WPA_MIXED_)
#endif
		return _security_type_str[value];
