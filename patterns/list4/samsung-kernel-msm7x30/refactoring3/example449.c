switch( pMlmSetKeysReq->edType ) {
      case eSIR_ED_CCMP:
         
#ifdef WLAN_FEATURE_11W
      case eSIR_ED_AES_128_CMAC:
#endif
        staIdx = psessionEntry->staId;
        break;

      default:
        break;
    }
