if ( ( pTLCb->uResCount > uResLen ) &&
           ( uRemaining > uTotalPktLen )
#if defined( FEATURE_WLAN_INTEGRATED_SOC )
           && ( uFlowMask & ( 1 << WDA_TXFLOW_FC ) )
#endif
          )
       {
          TLLOG2(VOS_TRACE( VOS_MODULE_ID_TL, VOS_TRACE_LEVEL_INFO_HIGH,
                   "WLAN TL:Chaining FC frame first on GetFrame"));

          vos_pkt_chain_packet( vosDataBuff, pTLCb->vosTxFCBuf, 1 /*true*/ );

          vos_atomic_set_U32( (v_U32_t*)&pTLCb->vosTxFCBuf, (v_U32_t)NULL);

          /*FC frames cannot be delayed*/
          pTLCb->bUrgent      = TRUE;

          /*Update remaining len from SSC */
          uRemaining        -= (usPktLen + WDA_DXE_HEADER_SIZE);

          /*Update resource count */
          pTLCb->uResCount -= uResLen;
       }
       else
       {
          TLLOGW(VOS_TRACE( VOS_MODULE_ID_TL, VOS_TRACE_LEVEL_WARN,
                "WLAN TL:send fc out of source %s", __FUNCTION__));
          ucResult = ( pTLCb->uResCount > uResLen )?VOS_TRUE:VOS_FALSE;
          break; /* Out of resources or reached max len */
       }
