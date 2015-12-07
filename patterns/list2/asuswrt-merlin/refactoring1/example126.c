if (net->ieee80211_ptr)
		*groups++ = &wireless_group;
#ifdef CONFIG_WIRELESS_EXT
	else if (net->wireless_handlers)
		*groups++ = &wireless_group;
#endif
