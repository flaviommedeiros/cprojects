switch(moduleID)
  {
    case VOS_MODULE_ID_TL:  
    {
      pGpModContext = &(gpVosContext->pTLContext); 
      break;
    }

#ifndef FEATURE_WLAN_INTEGRATED_SOC
    case VOS_MODULE_ID_BAL:
    {
      pGpModContext = &(gpVosContext->pBALContext);
      break;
    }

    case VOS_MODULE_ID_SAL:
    {
      pGpModContext = &(gpVosContext->pSALContext);
      break;
    }   

    case VOS_MODULE_ID_SSC:
    {
      pGpModContext = &(gpVosContext->pSSCContext); 
      break;
    }
#endif
#ifdef WLAN_BTAMP_FEATURE
    case VOS_MODULE_ID_BAP:
    {
        pGpModContext = &(gpVosContext->pBAPContext);
        break;
    }    
#endif //WLAN_BTAMP_FEATURE

#ifdef WLAN_SOFTAP_FEATURE
    case VOS_MODULE_ID_SAP:
    {
      pGpModContext = &(gpVosContext->pSAPContext);
      break;
    }
#endif

#ifdef FEATURE_WLAN_INTEGRATED_SOC
    case VOS_MODULE_ID_WDA:
    {
      pGpModContext = &(gpVosContext->pWDAContext);
      break;
    }
#endif
    case VOS_MODULE_ID_SME:
#ifndef FEATURE_WLAN_INTEGRATED_SOC
    case VOS_MODULE_ID_HAL:
#endif
    case VOS_MODULE_ID_PE:
    case VOS_MODULE_ID_HDD:
#ifdef WLAN_SOFTAP_FEATURE
    case VOS_MODULE_ID_HDD_SOFTAP:
#endif
    default:
    {     
      VOS_TRACE(VOS_MODULE_ID_VOSS, VOS_TRACE_LEVEL_ERROR, "%s: Module ID %i "
          "does not have its context allocated by VOSS", __func__, moduleID);
      VOS_ASSERT(0);
      return VOS_STATUS_E_INVAL;
    }
  }
