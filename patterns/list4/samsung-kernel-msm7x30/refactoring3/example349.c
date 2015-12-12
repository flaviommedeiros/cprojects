switch( message->type )
  {
  case WLANTL_TX_SIG_SUSPEND:
    vosStatus = WLANTL_SuspendCB( pvosGCtx,
                                 (WLANTL_SuspendCBType)message->bodyptr,
                                 message->reserved);
    break;
  case WLANTL_TX_RES_NEEDED:
    vosStatus = WLANTL_GetTxResourcesCB( pvosGCtx );
     break;
  
  case WLANTL_TX_FWD_CACHED:
    /*---------------------------------------------------------------------
     The data sent with the message has the following structure: 
       | 00 | ucBcastSignature | ucUcastSignature | ucSTAID |
       each field above is one byte
    ---------------------------------------------------------------------*/
    uData       = (v_U32_t)message->bodyptr; 
    ucSTAId     = ( uData & 0x000000FF); 
    ucUcastSig  = ( uData & 0x0000FF00)>>8; 
    ucBcastSig  = (v_U8_t)(( uData & 0x00FF0000)>>16); 
    vosStatus   = WLANTL_ForwardSTAFrames( pvosGCtx, ucSTAId, 
                                           ucUcastSig, ucBcastSig);
    break;
#ifdef WLAN_SOFTAP_FEATURE
  case WLANTL_TX_STAID_AC_IND:
      pTLCb = VOS_GET_TL_CB(pvosGCtx);
      if ( NULL == pTLCb )
      {
         TLLOGE(VOS_TRACE( VOS_MODULE_ID_TL, VOS_TRACE_LEVEL_ERROR,
              "WLAN TL:Invalid TL pointer from pvosGCtx on WLANTL_STAPktPending"));
         return VOS_STATUS_E_FAULT;
      }

      ucAC = message->bodyval &  WLANTL_AC_MASK;
      ucSTAId = (v_U8_t)message->bodyval >> WLANTL_STAID_OFFSET;  
      pTLCb->atlSTAClients[ucSTAId].aucACMask[ucAC] = 1; 

      vos_atomic_set_U8( &pTLCb->atlSTAClients[ucSTAId].ucPktPending, 1);
      vosStatus = WDA_DS_StartXmit(pvosGCtx);
      break;
#endif 
#if defined( FEATURE_WLAN_INTEGRATED_SOC )
  case WDA_DS_TX_START_XMIT:

    vosStatus = WDA_DS_TxFrames( pvosGCtx );

      break;

  case WDA_DS_FINISH_ULA:
    callbackContext = (void *)message->bodyval;
   
    callbackRoutine = message->bodyptr;
    callbackRoutine(callbackContext);
    break;
#endif

  default:
    /*no processing for now*/
    break;
  }
