switch( pMlmSetKeysReq->edType ) {
  case eSIR_ED_WEP40:
  case eSIR_ED_WEP104:
      // FIXME! Is this OK?
      if( 0 == pMlmSetKeysReq->numKeys ) {
#ifdef WLAN_SOFTAP_FEATURE
          tANI_U32 i;

          for(i=0; i < SIR_MAC_MAX_NUM_OF_DEFAULT_KEYS ;i++)
          { 
              palCopyMemory( pMac->hHdd,
                             (tANI_U8 *) &pSetStaKeyParams->key[i],
                             (tANI_U8 *) &pMlmSetKeysReq->key[i], sizeof( tSirKeys ));
          }
#endif
          pSetStaKeyParams->wepType = eSIR_WEP_STATIC;
          sessionEntry->limMlmState = eLIM_MLM_WT_SET_STA_KEY_STATE;
          MTRACE(macTrace(pMac, TRACE_CODE_MLM_STATE, sessionEntry->peSessionId, sessionEntry->limMlmState));
      }else {
          /*This case the keys are coming from upper layer so need to fill the 
          * key at the default wep key index and send to the HAL */
          palCopyMemory( pMac->hHdd,
                             (tANI_U8 *) &pSetStaKeyParams->key[defWEPIdx],
                             (tANI_U8 *) &pMlmSetKeysReq->key[0], sizeof( pMlmSetKeysReq->key[0] ));
          pMlmSetKeysReq->numKeys = SIR_MAC_MAX_NUM_OF_DEFAULT_KEYS;
      }
      break;
  case eSIR_ED_TKIP:
  case eSIR_ED_CCMP:
#ifdef FEATURE_WLAN_WAPI 
  case eSIR_ED_WPI: 
#endif
      {
          palCopyMemory( pMac->hHdd, (tANI_U8 *) &pSetStaKeyParams->key,
                         (tANI_U8 *) &pMlmSetKeysReq->key[0], sizeof( tSirKeys ));
      }
      break;
  default:
      break;
  }
