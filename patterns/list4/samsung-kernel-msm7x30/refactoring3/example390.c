switch(moduleId)
  {
    case VOS_MODULE_ID_TL:  
    {
      pModContext = gpVosContext->pTLContext;
      break;
    }

#ifndef FEATURE_WLAN_INTEGRATED_SOC
    case VOS_MODULE_ID_BAL:
    {
      pModContext = gpVosContext->pBALContext;
      break;
    }   

    case VOS_MODULE_ID_SAL:
    {
      pModContext = gpVosContext->pSALContext;
      break;
    }   

    case VOS_MODULE_ID_SSC:   
    {
      pModContext = gpVosContext->pSSCContext;
      break;
    }
#endif
#ifdef WLAN_BTAMP_FEATURE
    case VOS_MODULE_ID_BAP:
    {
        pModContext = gpVosContext->pBAPContext;
        break;
    }    
#endif //WLAN_BTAMP_FEATURE

#ifdef WLAN_SOFTAP_FEATURE
    case VOS_MODULE_ID_SAP:
    {
      pModContext = gpVosContext->pSAPContext;
      break;
    }

    case VOS_MODULE_ID_HDD_SOFTAP:
    {
      pModContext = gpVosContext->pHDDSoftAPContext;
      break;
    }
#endif

    case VOS_MODULE_ID_HDD:
    {
      pModContext = gpVosContext->pHDDContext;
      break;
    }

    case VOS_MODULE_ID_SME:
#ifndef FEATURE_WLAN_INTEGRATED_SOC
    case VOS_MODULE_ID_HAL:
#endif
    case VOS_MODULE_ID_PE:
    {
      /* 
      ** In all these cases, we just return the MAC Context
      */
      pModContext = gpVosContext->pMACContext;
      break;
    }

#ifdef FEATURE_WLAN_INTEGRATED_SOC
    case VOS_MODULE_ID_WDA:
    {
      /* For WDA module */
      pModContext = gpVosContext->pWDAContext;
      break;
    }
#endif

    case VOS_MODULE_ID_VOSS:
    {
      /* For SYS this is VOS itself*/
      pModContext = gpVosContext;
      break;
    }

    default:
    {
      VOS_TRACE(VOS_MODULE_ID_VOSS, VOS_TRACE_LEVEL_ERROR,"%s: Module ID %i "
          "does not have its context maintained by VOSS", __func__, moduleId);
      VOS_ASSERT(0);
      return NULL;
    }
  }
