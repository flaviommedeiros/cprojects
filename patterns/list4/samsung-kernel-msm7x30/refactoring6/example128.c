if ((psessionEntry->limSentCapsChangeNtf == false) && 
        (((!limIsNullSsid(&pBeacon->ssId)) && (limCmpSSid(pMac, &pBeacon->ssId, psessionEntry) == false)) || 
        ((SIR_MAC_GET_ESS(apNewCaps.capabilityInfo) != SIR_MAC_GET_ESS(psessionEntry->limCurrentBssCaps)) ||
         (SIR_MAC_GET_PRIVACY(apNewCaps.capabilityInfo) !=   SIR_MAC_GET_PRIVACY(psessionEntry->limCurrentBssCaps)) ||
         (SIR_MAC_GET_SHORT_PREAMBLE(apNewCaps.capabilityInfo) !=  SIR_MAC_GET_SHORT_PREAMBLE(psessionEntry->limCurrentBssCaps)) ||
         (SIR_MAC_GET_QOS(apNewCaps.capabilityInfo) !=   SIR_MAC_GET_QOS(psessionEntry->limCurrentBssCaps)) ||
         (newChannel !=  psessionEntry->currentOperChannel) 
#if (WNI_POLARIS_FW_PACKAGE == ADVANCED)
         || (LIM_BSS_CAPS_GET(HCF, psessionEntry->limCurrentBssQosCaps) !=
          pBeacon->propIEinfo.hcfEnabled)
#endif
         )))
    {

        /**
         * BSS capabilities have changed.
         * Inform Roaming.
         */
        len = sizeof(tSirMacCapabilityInfo) +
              sizeof(tSirMacAddr) + sizeof(tANI_U8) +
              3 * sizeof(tANI_U8) + // reserved fields
              pBeacon->ssId.length + 1;

        palCopyMemory( pMac->hHdd, apNewCaps.bssId,
                      psessionEntry->bssId,
                      sizeof(tSirMacAddr));
        if (newChannel != psessionEntry->currentOperChannel)
        {
            PELOGE(limLog(pMac, LOGE, FL("Channel Change from %d --> %d  - "
                                         "Ignoring beacon!\n"), 
                          psessionEntry->currentOperChannel, newChannel);)
            return;
        }
        else
            apNewCaps.channelId = psessionEntry->currentOperChannel;
        palCopyMemory( pMac->hHdd, (tANI_U8 *) &apNewCaps.ssId,
                      (tANI_U8 *) &pBeacon->ssId,
                      pBeacon->ssId.length + 1);

        psessionEntry->limSentCapsChangeNtf = true;
        limSendSmeWmStatusChangeNtf(pMac, eSIR_SME_AP_CAPS_CHANGED,
                                    (tANI_U32 *) &apNewCaps,
                                    len, psessionEntry->smeSessionId);
    }
