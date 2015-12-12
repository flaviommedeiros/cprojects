if (( pTLCb->tlBAPClient.vosPendingDataBuff ) &&
             ( WDA_TLI_MIN_RES_BAP <= pTLCb->uResCount ) &&
             ( 0 == pTLCb->ucTxSuspended )
#if defined( FEATURE_WLAN_INTEGRATED_SOC )
           && ( uFlowMask & ( 1 << WDA_TXFLOW_BAP ) )
#endif
          )
    {
      WDA_TLI_PROCESS_FRAME_LEN( pTLCb->tlBAPClient.vosPendingDataBuff,
                          usPktLen, uResLen, uTotalPktLen);

      VOS_ASSERT(usPktLen <= WLANTL_MAX_ALLOWED_LEN);

      if ( ( pTLCb->uResCount > (uResLen + WDA_TLI_MIN_RES_MF ) ) &&
           ( uRemaining > uTotalPktLen ))
      {
        TLLOG2(VOS_TRACE( VOS_MODULE_ID_TL, VOS_TRACE_LEVEL_INFO_HIGH,
                   "WLAN TL:Chaining BT-AMP frame on GetFrame"));

        vos_pkt_chain_packet( vosDataBuff,
                              pTLCb->tlBAPClient.vosPendingDataBuff,
                              1 /*true*/ );

        /*BAP frames cannot be delayed*/
        pTLCb->bUrgent      = TRUE;

        vos_atomic_set_U32( (v_U32_t*)&pTLCb->tlBAPClient.vosPendingDataBuff,
                            (v_U32_t)NULL);

        /*Update remaining len from SSC */
        uRemaining        -=  (usPktLen + WDA_DXE_HEADER_SIZE);

        /*Update resource count */
        pTLCb->uResCount  -= uResLen;
      }
      else
      {
#if defined( FEATURE_WLAN_INTEGRATED_SOC )
        ucResult = uResLen + WDA_TLI_MIN_RES_MF;
#else
        ucResult = ( pTLCb->uResCount > ( uResLen + WDA_TLI_MIN_RES_MF ) )?
                     VOS_TRUE:VOS_FALSE;
#endif
        break; /* Out of resources or reached max len */
      }
    }
    else if (( WDA_TLI_MIN_RES_DATA <= pTLCb->uResCount )&&
             ( 0 == pTLCb->ucTxSuspended )
#if defined( FEATURE_WLAN_INTEGRATED_SOC )
           && (( uFlowMask & ( 1 << WDA_TXFLOW_AC_BK ) ) || 
               ( uFlowMask & ( 1 << WDA_TXFLOW_AC_BE ) ) ||
               ( uFlowMask & ( 1 << WDA_TXFLOW_AC_VI ) ) || 
               ( uFlowMask & ( 1 << WDA_TXFLOW_AC_VO ) ))
#endif
          )
    {
      /*---------------------------------------------------------------------
        Check to see if there was any packet left behind previously due to
        size constraints
       ---------------------------------------------------------------------*/
      vosTempBuf = NULL;

      if ( NULL != pTLCb->vosTempBuf ) 
      {
        vosTempBuf          = pTLCb->vosTempBuf;
        pTLCb->vosTempBuf   = NULL;
        ucSTAId             = pTLCb->ucCachedSTAId; 
        ucAC                = pTLCb->ucCachedAC;
        pTLCb->atlSTAClients[ucSTAId].ucNoMoreData = 0;

        TLLOG2(VOS_TRACE( VOS_MODULE_ID_TL, VOS_TRACE_LEVEL_INFO_HIGH,
                   "WLAN TL:Chaining cached data frame on GetFrame"));
      }
      else
      {
        WLAN_TLGetNextTxIds( pvosGCtx, &ucSTAId);
        if (ucSTAId >= WLAN_MAX_STA_COUNT)
        {
         /* Packets start coming in even after insmod Without *
            starting Hostapd or Interface being up            *
            During which cases STAID is invaled and hence 
            the check. HalMsg_ScnaComplete Triggers */

            break;
        }
        /* ucCurrentAC should have correct AC to be served by calling
           WLAN_TLGetNextTxIds */
        ucAC = pTLCb->atlSTAClients[ucSTAId].ucCurrentAC;

        pTLCb->atlSTAClients[ucSTAId].ucNoMoreData = 1;
        TLLOG4(VOS_TRACE( VOS_MODULE_ID_TL, VOS_TRACE_LEVEL_INFO_LOW,
                   "WLAN TL: %s get one data frame, station ID %d ", __FUNCTION__, ucSTAId));
        /*-------------------------------------------------------------------
        Check to see that STA is valid and tx is not suspended
         -------------------------------------------------------------------*/
        if ( ( ! WLANTL_STA_ID_INVALID( ucSTAId ) ) &&
           ( 0 == pTLCb->atlSTAClients[ucSTAId].ucTxSuspended ) &&
           ( 0 == pTLCb->atlSTAClients[ucSTAId].fcStaTxDisabled) )
        {
          TLLOG4(VOS_TRACE( VOS_MODULE_ID_TL, VOS_TRACE_LEVEL_INFO_LOW,
                   "WLAN TL: %s sta id valid and not suspended ",__FUNCTION__));
          wSTAEvent = WLANTL_TX_EVENT;

          pfnSTAFsm = tlSTAFsm[pTLCb->atlSTAClients[ucSTAId].tlState].
                        pfnSTATbl[wSTAEvent];

          if ( NULL != pfnSTAFsm )
          {
            pTLCb->atlSTAClients[ucSTAId].ucNoMoreData = 0;
            vosStatus  = pfnSTAFsm( pvosGCtx, ucSTAId, &vosTempBuf);

            if (( VOS_STATUS_SUCCESS != vosStatus ) &&
                ( NULL != vosTempBuf ))
            {
                 pTLCb->atlSTAClients[ucSTAId].pfnSTATxComp( pvosGCtx,
                                                             vosTempBuf,
                                                             vosStatus );
                 vosTempBuf = NULL;
            }/* status success*/
          }/*NULL function state*/
        }/* valid STA id and ! suspended*/
        else
        {
           if ( ! WLANTL_STA_ID_INVALID( ucSTAId ) ) 
           {
                TLLOGE(VOS_TRACE( VOS_MODULE_ID_TL, VOS_TRACE_LEVEL_ERROR,
                  "WLAN TL:Not fetching frame because suspended for sta ID %d", 
                   ucSTAId));
           }
        }
      }/* data */

      if ( NULL != vosTempBuf )
      {
        WDA_TLI_PROCESS_FRAME_LEN( vosTempBuf, usPktLen, uResLen, uTotalPktLen);

        VOS_ASSERT( usPktLen <= WLANTL_MAX_ALLOWED_LEN);

        TLLOG4(VOS_TRACE( VOS_MODULE_ID_TL, VOS_TRACE_LEVEL_INFO_LOW,
                  "WLAN TL:Resources needed by frame: %d", uResLen));

        if ( ( pTLCb->uResCount >= (uResLen + WDA_TLI_MIN_RES_BAP ) ) &&
           ( uRemaining > uTotalPktLen )
#if defined( FEATURE_WLAN_INTEGRATED_SOC )
           && ( uFlowMask & ( 1 << ucAC ) )
#endif
           )
        {
          TLLOG2(VOS_TRACE( VOS_MODULE_ID_TL, VOS_TRACE_LEVEL_INFO_HIGH,
                    "WLAN TL:Chaining data frame on GetFrame"));

          vos_pkt_chain_packet( vosDataBuff, vosTempBuf, 1 /*true*/ );
          vosTempBuf =  NULL;

          /*Update remaining len from SSC */
          uRemaining        -= (usPktLen + WDA_DXE_HEADER_SIZE);

           /*Update resource count */
          pTLCb->uResCount  -= uResLen;

#ifdef WLAN_SOFTAP_FEATURE
          //fow control update
          pTLCb->atlSTAClients[ucSTAId].uIngress_length += uResLen;
          pTLCb->atlSTAClients[ucSTAId].uBuffThresholdMax = (pTLCb->atlSTAClients[ucSTAId].uBuffThresholdMax >= uResLen) ?
            (pTLCb->atlSTAClients[ucSTAId].uBuffThresholdMax - uResLen) : 0;
#endif

        }
        else
        {
          /* Store this for later tx - already fetched from HDD */
          pTLCb->vosTempBuf = vosTempBuf;
          pTLCb->ucCachedSTAId = ucSTAId;
          pTLCb->ucCachedAC    = ucAC;
#if defined( FEATURE_WLAN_INTEGRATED_SOC )
          ucResult = uResLen + WDA_TLI_MIN_RES_BAP;
          TLLOG2(VOS_TRACE( VOS_MODULE_ID_TL, VOS_TRACE_LEVEL_INFO_HIGH,
               "min %d res required by TL.", ucResult ));
#else
          ucResult = ( pTLCb->uResCount >= (uResLen + WDA_TLI_MIN_RES_BAP ))?
                       VOS_TRUE:VOS_FALSE;
#endif
          break; /* Out of resources or reached max len */
        }
      }
      else
      {
           for ( i = 0; i < WLAN_MAX_STA_COUNT; i++)
           {
              if ((pTLCb->atlSTAClients[i].ucExists) && 
                  (pTLCb->atlSTAClients[i].ucPktPending))
              {
                  /* There is station to be Served */
                  break;
              }
           }
           if (i >= WLAN_MAX_STA_COUNT)
           {
              /* No More to Serve Exit Get Frames */
              break;
           }
           else
           {
              /* More to be Served */
              continue;
           }
        } 
      }
    else
    {
      TLLOG2(VOS_TRACE( VOS_MODULE_ID_TL, VOS_TRACE_LEVEL_INFO_HIGH,
             "WLAN TL:Returning from GetFrame: resources = %d suspended = %d",
                 pTLCb->uResCount, pTLCb->ucTxSuspended));
#if defined( FEATURE_WLAN_INTEGRATED_SOC )
      /* TL is starving even when DXE is not in low resource condition 
         Return min resource number required and Let DXE deceide what to do */
      if(( 0 == pTLCb->ucTxSuspended ) && 
         (( uFlowMask & ( 1 << WDA_TXFLOW_AC_BK ) ) || 
          ( uFlowMask & ( 1 << WDA_TXFLOW_AC_BE ) ) ||
          ( uFlowMask & ( 1 << WDA_TXFLOW_AC_VI ) ) || 
          ( uFlowMask & ( 1 << WDA_TXFLOW_AC_VO ) )))
      {
         TLLOG1(VOS_TRACE(VOS_MODULE_ID_TL, VOS_TRACE_LEVEL_INFO,
             "WLAN TL:Returning from GetFrame: resources = %d",
                 pTLCb->uResCount));
         ucResult = WDA_TLI_MIN_RES_DATA;
      }
#endif
       break; /*out of min data resources*/
    }
