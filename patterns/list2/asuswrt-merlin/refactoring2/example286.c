#ifdef MANAGMENT_EXTERNAL_KEY
if (!(options->management_flags & MF_EXTERNAL_KEY))
#endif
	      notnull (options->priv_key_file, "private key file (--key) or PKCS#12 file (--pkcs12)");
