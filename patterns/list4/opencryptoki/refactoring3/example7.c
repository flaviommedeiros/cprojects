switch (mech->mechanism)
   {
      case CKM_SSL3_MASTER_KEY_DERIVE:
      {
         if (!derived_key){
            OCK_LOG_ERR(ERR_FUNCTION_FAILED);
            return CKR_FUNCTION_FAILED;
         }
         return ssl3_master_key_derive( sess, mech, base_key,
                                        pTemplate, ulCount, derived_key );
      }
      break ;

      case CKM_SSL3_KEY_AND_MAC_DERIVE:
      {
         return ssl3_key_and_mac_derive( sess, mech, base_key,
                                         pTemplate, ulCount );
      }
      break ;

/* Begin code contributed by Corrent corp. */
#ifndef NODH
      case CKM_DH_PKCS_DERIVE:
      {
         if (!derived_key){
            OCK_LOG_ERR(ERR_FUNCTION_FAILED);
            return CKR_FUNCTION_FAILED;
         }
         return dh_pkcs_derive( sess, mech, base_key,
                                pTemplate, ulCount, derived_key );
      }
      break ;
#endif
/* End code contributed by Corrent corp. */
      
      default:
         OCK_LOG_ERR(ERR_MECHANISM_INVALID);
         return CKR_MECHANISM_INVALID;
   }
