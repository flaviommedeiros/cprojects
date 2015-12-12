switch(pSmeStartBssReq->bssType)
        {
#ifdef WLAN_SOFTAP_FEATURE
            case eSIR_INFRA_AP_MODE:
                 psessionEntry->limSystemRole = eLIM_AP_ROLE;
                 psessionEntry->privacy = pSmeStartBssReq->privacy;
                 psessionEntry->fwdWPSPBCProbeReq = pSmeStartBssReq->fwdWPSPBCProbeReq;
                 psessionEntry->authType = pSmeStartBssReq->authType;
                 /* Store the DTIM period */
                 psessionEntry->dtimPeriod = (tANI_U8)pSmeStartBssReq->dtimPeriod;
                 /*Enable/disable UAPSD*/
                 psessionEntry->apUapsdEnable = pSmeStartBssReq->apUapsdEnable;
                 if (psessionEntry->pePersona == VOS_P2P_GO_MODE)
                 {
                     psessionEntry->proxyProbeRspEn = 0;
                 }
                 else
                 {
                     /* To detect PBC overlap in SAP WPS mode, Host handles
                      * Probe Requests.
                      */
                     if(SAP_WPS_DISABLED == pSmeStartBssReq->wps_state)
                     {
                         psessionEntry->proxyProbeRspEn = 1;
                     }
                     else
                     {
                         psessionEntry->proxyProbeRspEn = 0;
                     }
                 }
                 psessionEntry->ssidHidden = pSmeStartBssReq->ssidHidden;
                 psessionEntry->wps_state = pSmeStartBssReq->wps_state;
                 break;
#endif
            case eSIR_IBSS_MODE:
                 psessionEntry->limSystemRole = eLIM_STA_IN_IBSS_ROLE;
                 break;

            case eSIR_BTAMP_AP_MODE:
                 psessionEntry->limSystemRole = eLIM_BT_AMP_AP_ROLE;
                 break;

            case eSIR_BTAMP_STA_MODE:
                 psessionEntry->limSystemRole = eLIM_BT_AMP_STA_ROLE;
                 break;

                 /* There is one more mode called auto mode. which is used no where */

                 //FORBUILD -TEMPFIX.. HOW TO use AUTO MODE?????


            default:
                                   //not used anywhere...used in scan function
                 break;
        }
