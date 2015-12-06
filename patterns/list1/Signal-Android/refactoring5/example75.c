#ifdef HWAES_cbc_encrypt
if (mode==EVP_CIPH_CBC_MODE)
		    dat->stream.cbc = (cbc128_f)HWAES_cbc_encrypt;
		else
#endif
#ifdef HWAES_ctr32_encrypt_blocks
		if (mode==EVP_CIPH_CTR_MODE)
		    dat->stream.ctr = (ctr128_f)HWAES_ctr32_encrypt_blocks;
		else
#endif
		(void)0;
