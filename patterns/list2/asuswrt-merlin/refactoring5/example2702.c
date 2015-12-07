#ifndef HOSTAPD
if (addr == NULL ||
		    os_memcmp(addr, "\xff\xff\xff\xff\xff\xff",
			      IEEE80211_ADDR_LEN) == 0)
			return bsd_del_key(priv, NULL, key_idx);
		else
#endif /* HOSTAPD */
			return bsd_del_key(priv, addr, key_idx);
