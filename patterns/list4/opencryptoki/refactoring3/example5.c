switch (keytype) {
#if !(NOCDMF)
      case CKK_CDMF:
#endif
      case CKK_DES:
         rc = des_wrap_get_data( key2_obj->template, length_only, &data, &data_len );
         if (rc != CKR_OK){
            OCK_LOG_ERR(ERR_DES_WRAP_GETDATA);
            return rc;
         }
         break;

      case CKK_DES3:
         rc = des3_wrap_get_data( key2_obj->template, length_only, &data, &data_len );
         if (rc != CKR_OK){
            OCK_LOG_ERR(ERR_DES3_WRAP_GETDATA);
            return rc;
         }
         break;

      case CKK_RSA:
         rc = rsa_priv_wrap_get_data( key2_obj->template, length_only, &data, &data_len );
         if (rc != CKR_OK){
            OCK_LOG_ERR(ERR_RSA_WRAP_GETDATA);
            return rc;
         }
         break;

#if !(NODSA)
      case CKK_DSA:
         rc = dsa_priv_wrap_get_data( key2_obj->template, length_only, &data, &data_len );
         if (rc != CKR_OK){
            OCK_LOG_ERR(ERR_DSA_WRAP_GETDATA);
            return rc;
         }
         break;
#endif

      case CKK_GENERIC_SECRET:
         rc = generic_secret_wrap_get_data( key2_obj->template, length_only, &data, &data_len );
         if (rc != CKR_OK){
            OCK_LOG_ERR(ERR_GENERIC_WRAP_GETDATA);
            return rc;
         }
         break;
#ifndef NOAES
      case CKK_AES:
	 rc = aes_wrap_get_data( key2_obj->template, length_only, &data, &data_len );
	 if (rc != CKR_OK){
	    OCK_LOG_ERR(ERR_AES_WRAP_GETDATA);
	    return rc;
	 }
	 break;
#endif
      default:
         OCK_LOG_ERR(ERR_KEY_NOT_WRAPPABLE);
         return CKR_KEY_NOT_WRAPPABLE;
   }
