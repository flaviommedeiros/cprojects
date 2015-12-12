#ifdef WLAN_SOFTAP_FEATURE
if (VOS_STA_SAP_MODE == hdd_get_conparam())
   {
     pAdapter = hdd_open_adapter( pHddCtx, WLAN_HDD_SOFTAP, "softap.%d", 
         wlan_hdd_get_intf_addr(pHddCtx), FALSE );
   }
   else
   {
#endif
     pAdapter = hdd_open_adapter( pHddCtx, WLAN_HDD_INFRA_STATION, "wlan%d",
         wlan_hdd_get_intf_addr(pHddCtx), FALSE );
     if (pAdapter != NULL)
     {
#ifdef WLAN_FEATURE_P2P
         if ( pHddCtx->cfg_ini->isP2pDeviceAddrAdministrated )
         {
             vos_mem_copy( pHddCtx->p2pDeviceAddress.bytes,
                       pHddCtx->cfg_ini->intfMacAddr[0].bytes,
                       sizeof(tSirMacAddr));
             /* Generate the P2P Device Address.  This consists of the device's
              * primary MAC address with the locally administered bit set.
              */
             pHddCtx->p2pDeviceAddress.bytes[0] |= 0x02;
         }
         else
         {
             tANI_U8* p2p_dev_addr = wlan_hdd_get_intf_addr(pHddCtx);
             if (p2p_dev_addr != NULL)
             {
                vos_mem_copy(&pHddCtx->p2pDeviceAddress.bytes[0],
                             p2p_dev_addr, VOS_MAC_ADDR_SIZE);
             }
             else
             {
                hddLog(VOS_TRACE_LEVEL_FATAL,
                    "%s: Failed to allocate mac_address for p2p_device",
                    __FUNCTION__);
                goto err_close_adapter;
             }
         }

         pP2pAdapter = hdd_open_adapter( pHddCtx, WLAN_HDD_P2P_DEVICE, "p2p%d",
                           &pHddCtx->p2pDeviceAddress.bytes[0], FALSE );
         if ( NULL == pP2pAdapter )
         {
             hddLog(VOS_TRACE_LEVEL_FATAL,
                "%s: Failed to do hdd_open_adapter for P2P Device Interface",
                __FUNCTION__);
             goto err_close_adapter;
         }
#endif
     }
#ifdef WLAN_SOFTAP_FEATURE
   }
