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
