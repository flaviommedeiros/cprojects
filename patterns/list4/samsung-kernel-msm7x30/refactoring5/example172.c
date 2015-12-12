#ifdef WLAN_FEATURE_11AC
if (psessionEntry->vhtCapability)
            {
                ePhyChanBondState htSecondaryChannelOffset;
               /*Get 11ac cbState from 11n cbState*/
                 htSecondaryChannelOffset = limGet11ACPhyCBState(pMac, 
                                    psessionEntry->currentOperChannel,
                                    psessionEntry->htSecondaryChannelOffset);
                peSetResumeChannel( pMac, psessionEntry->currentOperChannel, htSecondaryChannelOffset);
            }
            else 
#endif
               peSetResumeChannel( pMac, psessionEntry->currentOperChannel, psessionEntry->htSecondaryChannelOffset);
