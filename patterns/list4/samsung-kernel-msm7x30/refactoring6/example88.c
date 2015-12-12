if( ( SIR_BAND_5_GHZ == limGetRFBand(nChannelNum))
#ifdef WLAN_FEATURE_P2P
      || (( pMac->lim.gpLimMlmScanReq != NULL) &&
          pMac->lim.gpLimMlmScanReq->p2pSearch )
#endif
      ) 
    {
        txFlag |= HAL_USE_BD_RATE2_FOR_MANAGEMENT_FRAME; 
    }
