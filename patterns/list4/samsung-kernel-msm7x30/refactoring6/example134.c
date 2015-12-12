if ( ( pMac->lim.gLimReturnAfterFirstMatch & 0x01 ) ||
             ( pMac->lim.gLim24Band11dScanDone && ( pMac->lim.gLimReturnAfterFirstMatch & 0x40 ) ) ||
             ( pMac->lim.gLim50Band11dScanDone && ( pMac->lim.gLimReturnAfterFirstMatch & 0x80 ) ) 
#ifdef WLAN_FEATURE_P2P
             || fFound
#endif
             )
/*
        if ((pMac->lim.gLimReturnAfterFirstMatch & 0x01) ||
            (pMac->lim.gLim24Band11dScanDone &&
             !(pMac->lim.gLimReturnAfterFirstMatch & 0xC0)) ||
            (pMac->lim.gLim50Band11dScanDone &&
             !(pMac->lim.gLimReturnAfterFirstMatch & 0xC0)) ||
            (pMac->lim.gLim24Band11dScanDone &&
             pMac->lim.gLim50Band11dScanDone &&
             pMac->lim.gLimReturnAfterFirstMatch & 0xC0))
*/
        {
            /**
             * Stop scanning and return the BSS description(s)
             * collected so far.
             */
            limLog(pMac,
                   LOGW,
                   FL("Completed scan: 24Band11dScan = %d, 50Band11dScan = %d BSS id\n"),
                   pMac->lim.gLim24Band11dScanDone,
                   pMac->lim.gLim50Band11dScanDone);

            //Need to disable the timers. If they fire, they will send END_SCAN
            //while we already send FINISH_SCAN here. This may mess up the gLimHalScanState
            limDeactivateAndChangeTimer(pMac, eLIM_MIN_CHANNEL_TIMER);
            limDeactivateAndChangeTimer(pMac, eLIM_MAX_CHANNEL_TIMER);
            //Set the resume channel to Any valid channel (invalid). 
            //This will instruct HAL to set it to any previous valid channel.
            peSetResumeChannel(pMac, 0, 0);
            limSendHalFinishScanReq( pMac, eLIM_HAL_FINISH_SCAN_WAIT_STATE );
            //limSendHalFinishScanReq( pMac, eLIM_HAL_FINISH_SCAN_WAIT_STATE );
        }
