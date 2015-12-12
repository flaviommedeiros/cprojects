#ifdef WLAN_SOFTAP_FEATURE
if (VOS_STA_SAP_MODE == hdd_get_conparam())
      {
         *vosFreeBuffer = gpVosPacketContext->uctxDataFreeListCount;  
          return VOS_STATUS_SUCCESS;
      }
      else
#endif
      pList = &gpVosPacketContext->txDataFreeList;
