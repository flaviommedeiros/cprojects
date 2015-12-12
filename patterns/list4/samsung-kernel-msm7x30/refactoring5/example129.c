#ifdef WLAN_SOFTAP_FEATURE
if (WLAN_STA_SOFTAP != pTLCb->atlSTAClients[ucSTAId].wSTADesc.wSTAType)
    {
#endif

      pTLCb->atlSTAClients[ucSTAId].aucACMask[ucAc] = 1; 

      vos_atomic_set_U8( &pTLCb->atlSTAClients[ucSTAId].ucPktPending, 1);

      /*------------------------------------------------------------------------
        Check if there are enough resources for transmission and tx is not
        suspended.
        ------------------------------------------------------------------------*/
       if (( pTLCb->uResCount >=  WDA_TLI_MIN_RES_DATA ) &&
          ( 0 == pTLCb->ucTxSuspended ))
      {
        TLLOG2(VOS_TRACE( VOS_MODULE_ID_TL, VOS_TRACE_LEVEL_INFO_HIGH,
              "Issuing Xmit start request to BAL"));
           WDA_DS_StartXmit(pvosGCtx);
      }
      else
      {
        /*---------------------------------------------------------------------
          No error code is sent because TL will resume tx autonomously if
          resources become available or tx gets resumed
          ---------------------------------------------------------------------*/
        VOS_TRACE( VOS_MODULE_ID_TL, VOS_TRACE_LEVEL_INFO_HIGH,
              "WLAN TL:Request to send but condition not met. Res: %d,Suspend: %d",
              pTLCb->uResCount, pTLCb->ucTxSuspended );
      }
#ifdef WLAN_SOFTAP_FEATURE
    }
    else
    {
      vosMsg.reserved = 0;
      vosMsg.bodyval  = 0;
      vosMsg.bodyval = (ucAc | (ucSTAId << WLANTL_STAID_OFFSET));
      vosMsg.type     = WLANTL_TX_STAID_AC_IND;
      return vos_tx_mq_serialize( VOS_MQ_ID_TL, &vosMsg);
    }
