#ifdef CONFIG_IEEE80211W
if (use_sha256)
		hmac_sha256_vector(smk, PMK_LEN, 5, addr, len, hash);
	else
#endif /* CONFIG_IEEE80211W */
		hmac_sha1_vector(smk, PMK_LEN, 5, addr, len, hash);
