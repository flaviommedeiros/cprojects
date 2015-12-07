#ifdef CONFIG_IEEE80211W
if (use_sha256)
		hmac_sha256_vector(pmk, pmk_len, 3, addr, len, hash);
	else
#endif /* CONFIG_IEEE80211W */
		hmac_sha1_vector(pmk, pmk_len, 3, addr, len, hash);
