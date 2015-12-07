if (cipher_kt_mode_cbc(cipher)
#ifdef ENABLE_OFB_CFB_MODE
	      || cipher_kt_mode_ofb_cfb(cipher)
#endif
	      )
	    {
	      const char *var_key_size =
		  (EVP_CIPHER_flags (cipher) & EVP_CIPH_VARIABLE_LENGTH) ?
		       "variable" : "fixed";
	      const char *ssl_only = cipher_kt_mode_ofb_cfb(cipher) ?
		  " (TLS client/server mode)" : "";

	      printf ("%s %d bit default key (%s)%s\n", OBJ_nid2sn (nid),
		      EVP_CIPHER_key_length (cipher) * 8, var_key_size,
		      ssl_only);
	    }
