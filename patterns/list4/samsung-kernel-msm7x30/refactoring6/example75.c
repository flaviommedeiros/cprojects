if ( 
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,38))
                (!pairwise)
#else
                (!mac_addr || is_broadcast_ether_addr(mac_addr)) 
#endif
           )
        {
            /* set group key*/
            VOS_TRACE( VOS_MODULE_ID_HDD, VOS_TRACE_LEVEL_INFO,
                    "%s- %d: setting Broacast key",
                    __func__, __LINE__);
            setKey.keyDirection = eSIR_RX_ONLY;
            vos_mem_copy(setKey.peerMac,groupmacaddr,WNI_CFG_BSSID_LEN);
        }
        else
        {
            /* set pairwise key*/
            VOS_TRACE( VOS_MODULE_ID_HDD, VOS_TRACE_LEVEL_INFO,
                    "%s- %d: setting pairwise key",
                    __func__, __LINE__);
            setKey.keyDirection = eSIR_TX_RX;
            vos_mem_copy(setKey.peerMac, mac_addr,WNI_CFG_BSSID_LEN);
        }
