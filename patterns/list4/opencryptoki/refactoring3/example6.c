switch (mech->mechanism) {
#if !(NOCMF)
      case CKM_CDMF_ECB:
      case CKM_CDMF_CBC:
#endif
      case CKM_DES_ECB:
      case CKM_DES_CBC:
      case CKM_DES3_ECB:
      case CKM_DES3_CBC:
         rc = ckm_des_wrap_format( length_only, &data, &data_len );
         if (rc != CKR_OK) {
            OCK_LOG_ERR(ERR_DES_WRAP_FORMAT);
            if (data) free( data );
            return rc;
         }
         break;
#ifndef NOAES
      case CKM_AES_ECB:
      case CKM_AES_CBC:
      case CKM_AES_CTR:
      case CKM_AES_OFB:
      case CKM_AES_CFB8:
      case CKM_AES_CFB64:
      case CKM_AES_CFB128:
	 rc = ckm_aes_wrap_format( length_only, &data, &data_len );
	 if (rc != CKR_OK) {
	    OCK_LOG_ERR(ERR_AES_WRAP_FORMAT);
	    if (data) free( data );
	    return rc;
	 }
	 break;
#endif
#if !(NOCMF)
      case CKM_CDMF_CBC_PAD:
#endif
      case CKM_DES_CBC_PAD:
      case CKM_DES3_CBC_PAD:
      case CKM_AES_CBC_PAD:
         // these mechanisms pad themselves
         //
         break;

      case CKM_RSA_PKCS:
      case CKM_RSA_X_509:
         break;

      default:
         OCK_LOG_ERR(ERR_KEY_NOT_WRAPPABLE);
         return CKR_KEY_NOT_WRAPPABLE;
   }
