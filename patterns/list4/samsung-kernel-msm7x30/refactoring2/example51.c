#if defined(FEATURE_WLAN_NON_INTEGRATED_SOC)
if (HAL_STATUS_SUCCESS(palWriteRegister(hHdd, regAddr, regValue)))
#elif defined(FEATURE_WLAN_INTEGRATED_SOC)
         if (eWLAN_PAL_STATUS_SUCCESS == wpalDbgWriteRegister(regAddr, regValue))
#endif
         {
            status = VOS_STATUS_SUCCESS;
         }
         else
         {
            status = VOS_STATUS_E_FAILURE;
         }
