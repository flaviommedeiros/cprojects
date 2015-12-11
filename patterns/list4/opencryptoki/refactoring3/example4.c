switch (mech->mechanism) {
      case CKM_DES_KEY_GEN:
            rc = ckm_des_key_gen( key_obj->template );
            break;

         case CKM_DES3_KEY_GEN:
            rc = ckm_des3_key_gen( key_obj->template );
            break;

#if !(NOCDMF)
         case CKM_CDMF_KEY_GEN:
            rc = ckm_cdmf_key_gen( key_obj->template );
            break;
#endif

         case CKM_SSL3_PRE_MASTER_KEY_GEN:
            rc = ckm_ssl3_pre_master_key_gen( key_obj->template, mech );
            break;
#ifndef NOAES
	 case CKM_AES_KEY_GEN:
	    rc = ckm_aes_key_gen( key_obj->template );
	    break;
#endif
      default:
         OCK_LOG_ERR(ERR_MECHANISM_INVALID);
         rc = CKR_MECHANISM_INVALID;
   }
