#ifdef ANI_AP_SDK
if (!pMeasReq->channelList.numChannels ||
        ((pMeasReq->measControl.periodicMeasEnabled) &&
         (!pMeasReq->measIndPeriod)) ||
        (pMeasReq->measIndPeriod &&
         ((pMeasReq->measIndPeriod < 1))) ||
        !pMeasReq->measDuration.shortTermPeriod ||
        ((pMeasReq->measDuration.shortTermPeriod < 1)) ||
        !pMeasReq->measDuration.averagingPeriod ||
        (pMeasReq->measDuration.averagingPeriod <
         pMeasReq->measDuration.shortTermPeriod) ||
        !pMeasReq->measDuration.shortChannelScanDuration ||
        ((pMeasReq->measDuration.shortChannelScanDuration <
          1)) ||
        !pMeasReq->measDuration.longChannelScanDuration ||
        (pMeasReq->measDuration.longChannelScanDuration <
         pMeasReq->measDuration.shortChannelScanDuration) ||
        ((pMeasReq->measDuration.longChannelScanDuration <
          1)))
#else
    if (!pMeasReq->channelList.numChannels ||
        ((pMeasReq->measControl.periodicMeasEnabled) &&
         (!pMeasReq->measIndPeriod)) ||
        (pMeasReq->measIndPeriod &&
         ((pMeasReq->measIndPeriod < SYS_TICK_DUR_MS))) ||
        !pMeasReq->measDuration.shortTermPeriod ||
        ((pMeasReq->measDuration.shortTermPeriod < SYS_TICK_DUR_MS)) ||
        !pMeasReq->measDuration.averagingPeriod ||
        (pMeasReq->measDuration.averagingPeriod <
         pMeasReq->measDuration.shortTermPeriod) ||
        !pMeasReq->measDuration.shortChannelScanDuration ||
        ((pMeasReq->measDuration.shortChannelScanDuration <
          SYS_TICK_DUR_MS)) ||
        !pMeasReq->measDuration.longChannelScanDuration ||
        (pMeasReq->measDuration.longChannelScanDuration <
         pMeasReq->measDuration.shortChannelScanDuration) ||
        ((pMeasReq->measDuration.longChannelScanDuration <
          SYS_TICK_DUR_MS)))


#endif
    {
        limLog(pMac, LOGW,
               FL("Received MEASUREMENT_REQ with invalid data\n"));

        return eANI_BOOLEAN_FALSE;
    }
    else
        return eANI_BOOLEAN_TRUE;
