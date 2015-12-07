#ifdef EAP_AKA_PRIME
if (data->eap_method == EAP_TYPE_AKA_PRIME)
		sha256_vector(1, &addr, &len, hash);
	else
#endif /* EAP_AKA_PRIME */
		sha1_vector(1, &addr, &len, hash);
