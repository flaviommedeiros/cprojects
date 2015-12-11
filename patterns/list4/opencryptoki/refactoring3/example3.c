switch (ctx->mech.mechanism) {
      case CKM_CDMF_ECB:
      case CKM_DES_ECB:
         return des_ecb_encrypt_final( sess,     length_only,
                                       ctx,
                                       out_data, out_data_len );

      case CKM_CDMF_CBC:
      case CKM_DES_CBC:
         return des_cbc_encrypt_final( sess,     length_only,
                                       ctx,
                                       out_data, out_data_len );

      case CKM_DES_CBC_PAD:
      case CKM_CDMF_CBC_PAD:
         return des_cbc_pad_encrypt_final( sess,     length_only,
                                           ctx,
                                           out_data, out_data_len );

      case CKM_DES_OFB64:
         get_keytype(ctx->key, &keytype);
         if (keytype == CKK_DES3) {
            return des3_ofb_encrypt_final( sess,     length_only,
                                           ctx,
                                           out_data, out_data_len );
         } else {
            OCK_LOG_ERR(ERR_KEY_TYPE_INCONSISTENT);
            return CKR_KEY_TYPE_INCONSISTENT;
         }

      case CKM_DES_CFB8:
         get_keytype(ctx->key, &keytype);
         if (keytype == CKK_DES3) {
            return des3_cfb_encrypt_final( sess,     length_only,
                                           ctx,
                                           out_data, out_data_len, 0x01);
         } else {
            OCK_LOG_ERR(ERR_KEY_TYPE_INCONSISTENT);
            return CKR_KEY_TYPE_INCONSISTENT;
         }

      case CKM_DES_CFB64:
         get_keytype(ctx->key, &keytype);
         if (keytype == CKK_DES3) {
            return des3_cfb_encrypt_final( sess,     length_only,
                                           ctx,
                                           out_data, out_data_len, 0x08);
         } else {
            OCK_LOG_ERR(ERR_KEY_TYPE_INCONSISTENT);
            return CKR_KEY_TYPE_INCONSISTENT;
         }

      case CKM_DES3_ECB:
         return des3_ecb_encrypt_final( sess,     length_only,
                                        ctx,
                                        out_data, out_data_len );

      case CKM_DES3_CBC:
         return des3_cbc_encrypt_final( sess,     length_only,
                                        ctx,
                                        out_data, out_data_len );

      case CKM_DES3_CBC_PAD:
         return des3_cbc_pad_encrypt_final( sess,     length_only,
                                            ctx,
                                            out_data, out_data_len );
#ifndef NOAES
      case CKM_AES_ECB:
	 return aes_ecb_encrypt_final( sess,     length_only,
			 	       ctx,
				       out_data, out_data_len );
	 
      case CKM_AES_CBC:
	 return aes_cbc_encrypt_final( sess,     length_only,
			 	       ctx,
				       out_data, out_data_len );
	 
      case CKM_AES_CBC_PAD:
	 return aes_cbc_pad_encrypt_final( sess,     length_only,
			 		   ctx,
					   out_data, out_data_len );

     case CKM_AES_CTR:
	 return aes_ctr_encrypt_final( sess,     length_only,
				       ctx,
				       out_data, out_data_len );
     case CKM_AES_OFB:
         return aes_ofb_encrypt_final( sess,     length_only,
                                       ctx,
                                       out_data, out_data_len );

     case CKM_AES_CFB8:
         return aes_cfb_encrypt_final( sess,     length_only,
                                       ctx,
                                       out_data, out_data_len, 0x01);
     case CKM_AES_CFB64:
         return aes_cfb_encrypt_final( sess,     length_only,
                                       ctx,
                                       out_data, out_data_len, 0x08);
     case CKM_AES_CFB128:
         return aes_cfb_encrypt_final( sess,     length_only,
                                       ctx,
                                       out_data, out_data_len, 0x10);
#endif
      default:
         return CKR_MECHANISM_INVALID;
   }
