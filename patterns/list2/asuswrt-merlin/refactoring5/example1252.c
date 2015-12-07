#ifdef CONFIG_IEEE80211W
if (use_sha256)
		sha256_prf(pmk, pmk_len, label, data, sizeof(data),
			   ptk, ptk_len);
	else
#endif /* CONFIG_IEEE80211W */
		sha1_prf(pmk, pmk_len, label, data, sizeof(data), ptk,
			 ptk_len);
