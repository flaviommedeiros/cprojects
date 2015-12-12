if (pMac->roam.configParam.isFastTransitionEnabled
#ifdef FEATURE_WLAN_LFR
         || csrRoamIsFastRoamEnabled(pMac)
#endif
         )
        {
            dwTmp = pal_cpu_to_be32(TRUE); 
            palCopyMemory( pMac->hHdd, pBuf, &dwTmp, sizeof(tAniBool) );
            pBuf += sizeof(tAniBool);        
        }
        else
        {
            dwTmp = pal_cpu_to_be32(FALSE); 
            palCopyMemory( pMac->hHdd, pBuf, &dwTmp, sizeof(tAniBool) );
            pBuf += sizeof(tAniBool);        
        }
