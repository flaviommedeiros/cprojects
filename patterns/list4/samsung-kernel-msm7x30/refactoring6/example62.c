if(0 == ucUnicastBroadcastType
#ifdef FEATURE_ON_CHIP_REORDERING
   && (WLANHAL_IsOnChipReorderingEnabledForTID(pvosGCtx, ucSTAId, ucTid) != TRUE)
#endif
)
{
  /* replay check code : check whether replay check is needed or not */
  if(VOS_TRUE == pTLCb->atlSTAClients[ucSTAId].ucIsReplayCheckValid)
  {
      /* replay check is needed for the station */

      /* check whether frame is AMSDU frame */
      if ( 0 != ucAsf )
      {
          /* Since virgo can't send AMSDU frames this leg of the code 
             was not tested properly, it needs to be tested properly*/
          /* Frame is AMSDU frame. As per 802.11n only first
             subframe will have replay counter */
          ucEsf =  WDA_GET_RX_ESF( aucBDHeader );
          if( 0 != ucEsf )
          {
              v_BOOL_t status;
              /* Getting 48-bit replay counter from the RX BD */
              ullcurrentReplayCounter = WDA_DS_GetReplayCounter(aucBDHeader);
 
              VOS_TRACE( VOS_MODULE_ID_TL, VOS_TRACE_LEVEL_INFO,
               "WLAN TL: AMSDU currentReplayCounter [0x%llX]\n",ullcurrentReplayCounter);
              
              /* Getting 48-bit previous replay counter from TL control  block */
              ullpreviousReplayCounter = pTLCb->atlSTAClients[ucSTAId].ullReplayCounter[ucTid];

              VOS_TRACE( VOS_MODULE_ID_TL, VOS_TRACE_LEVEL_INFO,
               "WLAN TL: AMSDU previousReplayCounter [0x%llX]\n",ullpreviousReplayCounter);

              /* It is first subframe of AMSDU thus it
                 conatains replay counter perform the
                 replay check for this first subframe*/
              status =  WLANTL_IsReplayPacket( ullcurrentReplayCounter, ullpreviousReplayCounter);
              if(VOS_FALSE == status)
              {
                   /* Not a replay paket, update previous replay counter in TL CB */    
                   pTLCb->atlSTAClients[ucSTAId].ullReplayCounter[ucTid] = ullcurrentReplayCounter;
              }
              else
              {
                  VOS_TRACE( VOS_MODULE_ID_TL, VOS_TRACE_LEVEL_ERROR,
                  "WLAN TL: AMSDU Drop the replay packet with PN : [0x%llX]\n",ullcurrentReplayCounter);

                  pTLCb->atlSTAClients[ucSTAId].ulTotalReplayPacketsDetected++;
                  VOS_TRACE( VOS_MODULE_ID_TL, VOS_TRACE_LEVEL_ERROR,
                  "WLAN TL: AMSDU total dropped replay packets on STA ID  %X is [0x%lX]\n",
                  ucSTAId,  pTLCb->atlSTAClients[ucSTAId].ulTotalReplayPacketsDetected);

                  /* Drop the packet */
                  vos_pkt_return_packet(vosDataBuff);
                  return VOS_STATUS_SUCCESS;
              }
          }
      }
      else
      {
           v_BOOL_t status;

           /* Getting 48-bit replay counter from the RX BD */
           ullcurrentReplayCounter = WDA_DS_GetReplayCounter(aucBDHeader);

           VOS_TRACE( VOS_MODULE_ID_TL, VOS_TRACE_LEVEL_INFO,
             "WLAN TL: Non-AMSDU currentReplayCounter [0x%llX]\n",ullcurrentReplayCounter);

           /* Getting 48-bit previous replay counter from TL control  block */
           ullpreviousReplayCounter = pTLCb->atlSTAClients[ucSTAId].ullReplayCounter[ucTid];

           VOS_TRACE( VOS_MODULE_ID_TL, VOS_TRACE_LEVEL_INFO,
               "WLAN TL: Non-AMSDU previousReplayCounter [0x%llX]\n",ullpreviousReplayCounter);

           /* It is not AMSDU frame so perform 
              reaply check for each packet, as
              each packet contains valid replay counter*/ 
           status =  WLANTL_IsReplayPacket( ullcurrentReplayCounter, ullpreviousReplayCounter);
           if(VOS_FALSE == status)
           {
                /* Not a replay paket, update previous replay counter in TL CB */    
                pTLCb->atlSTAClients[ucSTAId].ullReplayCounter[ucTid] = ullcurrentReplayCounter;
           }
           else
           {
              VOS_TRACE( VOS_MODULE_ID_TL, VOS_TRACE_LEVEL_ERROR,
               "WLAN TL: Non-AMSDU Drop the replay packet with PN : [0x%llX]\n",ullcurrentReplayCounter);

               pTLCb->atlSTAClients[ucSTAId].ulTotalReplayPacketsDetected++;
               VOS_TRACE( VOS_MODULE_ID_TL, VOS_TRACE_LEVEL_ERROR,
                "WLAN TL: Non-AMSDU total dropped replay packets on STA ID %X is [0x%lX]\n",
                ucSTAId, pTLCb->atlSTAClients[ucSTAId].ulTotalReplayPacketsDetected);

               /* Repaly packet, drop the packet */
               vos_pkt_return_packet(vosDataBuff);
               return VOS_STATUS_SUCCESS;
           }
      }
  }
}
