if ( ( 0 == pStaClient->wSTADesc.ucSwFrameTXXlation ) &&
          ( 0 == tlMetaInfo.ucBcast ) &&
          ( 0 == tlMetaInfo.ucMcast )
#ifdef FEATURE_WLAN_WAPI
          && ( tlMetaInfo.ucIsWai != 1 )
#endif
        )
     {
#ifdef WLAN_PERF 
        v_U32_t uFastFwdOK = 0;

        /* HW based translation. See if the frame could be fast forwarded */
        WDA_TLI_FastHwFwdDataFrame( pvosGCtx, vosDataBuff , &vosStatus, 
                                   &uFastFwdOK, &tlMetaInfo, &pStaClient->wSTADesc);

        if( VOS_STATUS_SUCCESS == vosStatus )
        {
            if(uFastFwdOK)
            {
                /* Packet could be fast forwarded now */
                vos_pkt_set_user_data_ptr( vosDataBuff, VOS_PKT_USER_DATA_ID_TL, 
                               (v_PVOID_t)pStaClient->pfnSTATxComp );

                *pvosDataBuff = vosDataBuff;

                /* TODO: Do we really need to update WLANTL_HSHandleTXFrame() 
                   stats for every pkt? */
                pStaClient->auTxCount[tlMetaInfo.ucTID]++;
                return vosStatus;
             }
             /* can't be fast forwarded, fall through normal (slow) path. */
        }
        else
        {

            TLLOGE(VOS_TRACE( VOS_MODULE_ID_TL, VOS_TRACE_LEVEL_ERROR,
                       "WLAN TL:Failed while attempting to fastFwd BD %d", vosStatus));
            *pvosDataBuff = NULL;
            return vosStatus;
        }
#endif /*WLAN_PERF*/
     }
     else
     {
        /* SW based translation */

#ifdef FEATURE_WLAN_WAPI
       gUcIsWai = tlMetaInfo.ucIsWai,
#endif

       vosStatus = WLANTL_Translate8023To80211Header( vosDataBuff, &vosStatus,
                                                   pTLCb, ucSTAId,
                                                   tlMetaInfo.ucUP, &ucWDSEnabled, &extraHeadSpace);
       if ( VOS_STATUS_SUCCESS != vosStatus )
       {
          TLLOGE(VOS_TRACE( VOS_MODULE_ID_TL, VOS_TRACE_LEVEL_ERROR,
                    "WLAN TL:Error when translating header WLANTL_STATxAuth"));
          return vosStatus;
       }

       TLLOG4(VOS_TRACE( VOS_MODULE_ID_TL, VOS_TRACE_LEVEL_INFO_LOW,
                    "WLAN TL software translation success \n"));
       ucSwFrmXtl = 1;
       tlMetaInfo.ucDisableFrmXtl = 1;
    }
