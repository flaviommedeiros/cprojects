switch (pActionHdr->actionID)
            {
#ifdef ANI_SUPPORT_11H
                case SIR_MAC_ACTION_MEASURE_REQUEST_ID:
                    if(psessionEntry->lim11hEnable)
                    {
                        __limProcessMeasurementRequestFrame(pMac, pRxPacketInfo);
                    }
                    break;

                case SIR_MAC_ACTION_TPC_REQUEST_ID:
                    if ((psessionEntry->limSystemRole == eLIM_STA_ROLE) ||
                        (pessionEntry->limSystemRole == eLIM_AP_ROLE))
                    {
                        if(psessionEntry->lim11hEnable)
                        {
                            __limProcessTpcRequestFrame(pMac, pRxPacketInfo);
                        }
                    }
                    break;

#endif
                case SIR_MAC_ACTION_CHANNEL_SWITCH_ID:
                    if (psessionEntry->limSystemRole == eLIM_STA_ROLE)
                    {
                        __limProcessChannelSwitchActionFrame(pMac, pRxPacketInfo,psessionEntry);
                    }
                    break;
                default:
                    PELOGE(limLog(pMac, LOGE, FL("Spectrum mgmt action id %d not handled\n"), pActionHdr->actionID);)
                    break;
            }
