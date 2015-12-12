switch(msg_type)
   {
      case eWNI_SME_ADDTS_RSP:
         pEntry = csrLLPeekHead(&pMac->sme.smeCmdActiveList, LL_ACCESS_LOCK);
         if( pEntry )
         {
             pCommand = GET_BASE_ADDR(pEntry, tSmeCmd, Link);
             if( eSmeCommandAddTs == pCommand->command )
             {
                status = sme_QosProcessAddTsRsp(pMac, pMsgBuf);
                if( csrLLRemoveEntry( &pMac->sme.smeCmdActiveList, pEntry, LL_ACCESS_LOCK ) )
                {
                   qosReleaseCommand( pMac, pCommand );
                }
                smeProcessPendingQueue( pMac );
             }
         }
         break;
      case eWNI_SME_DELTS_RSP:
         pEntry = csrLLPeekHead(&pMac->sme.smeCmdActiveList, LL_ACCESS_LOCK);
         if( pEntry )
         {
             pCommand = GET_BASE_ADDR(pEntry, tSmeCmd, Link);
             if( eSmeCommandDelTs == pCommand->command )
             {
                status = sme_QosProcessDelTsRsp(pMac, pMsgBuf);
                if( csrLLRemoveEntry( &pMac->sme.smeCmdActiveList, pEntry, LL_ACCESS_LOCK ) )
                {
                   qosReleaseCommand( pMac, pCommand );
                }
                smeProcessPendingQueue( pMac );
             }
         }
         break;
      case eWNI_SME_DELTS_IND:
         status = sme_QosProcessDelTsInd(pMac, pMsgBuf);
         break;
#ifdef WLAN_FEATURE_VOWIFI_11R
      case eWNI_SME_FT_AGGR_QOS_RSP:
         status = sme_QosProcessAggrQosRsp(pMac, pMsgBuf);
         break;
#endif

      default:
         //err msg
         VOS_TRACE(VOS_MODULE_ID_SME, VOS_TRACE_LEVEL_ERROR, 
                   "%s: %d: unknown msg type = %d",
                   __FUNCTION__, __LINE__, msg_type);
         break;
   }
