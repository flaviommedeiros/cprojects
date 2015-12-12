if(csrIsConnStateIbss(pMac, sessionId) || csrIsBTAMP(pMac, sessionId) 
#ifdef WLAN_SOFTAP_FEATURE
               || csrIsConnStateConnectedInfraAp(pMac, sessionId)
#endif
               )
            {
                //co-exist with IBSS or BT-AMP or Soft-AP mode is not supported
                smsLog(pMac, LOGW, "OEM DATA REQ is not allowed due to IBSS|BTAMP|SAP exist in session %d\n", sessionId);
                status = eHAL_STATUS_CSR_WRONG_STATE;
                break;
            }
