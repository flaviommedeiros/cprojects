if (!(cipher_kt_mode_cbc(kt->cipher)
#ifdef ENABLE_OFB_CFB_MODE
	      || (cfb_ofb_allowed && cipher_kt_mode_ofb_cfb(kt->cipher))
#endif
	      ))
	  msg (M_FATAL, "Cipher '%s' mode not supported", ciphername);
