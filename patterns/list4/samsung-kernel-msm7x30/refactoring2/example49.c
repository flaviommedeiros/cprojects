#if defined(FEATURE_WLAN_NON_INTEGRATED_SOC)
if (HAL_STATUS_SUCCESS(palReadRegister(hHdd, regAddr, pRegValue )))
#elif defined(FEATURE_WLAN_INTEGRATED_SOC)
         if (eWLAN_PAL_STATUS_SUCCESS == wpalDbgReadRegister(regAddr, pRegValue))
#endif
         {
            status = VOS_STATUS_SUCCESS;
         }
         else
         {  
            status = VOS_STATUS_E_FAILURE;
         }
