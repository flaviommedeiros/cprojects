if( ( SIR_BAND_5_GHZ == limGetRFBand(psessionEntry->currentOperChannel))
#ifdef WLAN_FEATURE_P2P
       || ( psessionEntry->pePersona == VOS_P2P_CLIENT_MODE ) ||
         ( psessionEntry->pePersona == VOS_P2P_GO_MODE)
#endif
         )
    {
        txFlag |= HAL_USE_BD_RATE2_FOR_MANAGEMENT_FRAME;
    }
