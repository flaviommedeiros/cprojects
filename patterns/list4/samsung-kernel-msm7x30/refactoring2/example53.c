#if defined(FEATURE_WLAN_NON_INTEGRATED_SOC)
if (HAL_STATUS_SUCCESS(palReadDeviceMemory(pvosGCTx, memAddr, (void *)pBuf, nLen)))
#elif defined(FEATURE_WLAN_INTEGRATED_SOC)
         if (eWLAN_PAL_STATUS_SUCCESS == wpalDbgReadMemory(memAddr, (void *)pBuf, nLen)) 
#endif
         {
            status = VOS_STATUS_SUCCESS;
         }
         else
         {
            status = VOS_STATUS_E_FAILURE;
         }
