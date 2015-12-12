if ((( 0 == pTLCb->atlSTAClients[ucSTAId].ucExists ) ||
          ( (0 != pTLCb->atlSTAClients[ucSTAId].ucRxBlocked)
#ifdef WLAN_SOFTAP_FEATURE
            ///@@@: xg: no checking in SOFTAP for now, will revisit later
            && (WLAN_STA_SOFTAP != pTLCb->atlSTAClients[ucSTAId].wSTADesc.wSTAType)
#endif
          ) ||
          ( WLANTL_STA_DISCONNECTED == pTLCb->atlSTAClients[ucSTAId].tlState)) &&
            /*Dont buffer Broadcast/Multicast frames. If AP transmits bursts of Broadcast/Multicast data frames, 
             * libra buffers all Broadcast/Multicast packets after authentication with AP, 
             * So it will lead to low resource condition in Rx Data Path.*/
          ((WDA_IS_RX_BCAST(pvBDHeader) == 0)))
      {
        uDPUSig = WDA_GET_RX_DPUSIG( pvBDHeader );
          //Station has not yet been registered with TL - cache the frame
        WLANTL_CacheSTAFrame( pTLCb, ucSTAId, vosTempBuff, uDPUSig, broadcast, ucFrmType);
        vosTempBuff = vosDataBuff;
        continue;
      }
