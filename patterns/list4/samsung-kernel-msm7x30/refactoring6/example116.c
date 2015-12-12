if((limMsg->type != WDA_ADD_BSS_RSP) &&
        (limMsg->type != WDA_DELETE_BSS_RSP) &&
        (limMsg->type != WDA_ADD_STA_RSP) &&
        (limMsg->type != WDA_ADD_STA_SELF_RSP) &&
        (limMsg->type != WDA_DEL_STA_SELF_RSP) &&
        (limMsg->type != WDA_DELETE_STA_RSP)&&
        (limMsg->type != WDA_SET_BSSKEY_RSP)&&
        (limMsg->type != WDA_SET_STAKEY_RSP)&&
        (limMsg->type != WDA_SET_STA_BCASTKEY_RSP) &&
        (limMsg->type != eWNI_SME_START_REQ) &&
        (limMsg->type != WDA_AGGR_QOS_RSP) &&
        (limMsg->type != WDA_REMOVE_BSSKEY_RSP) &&
        (limMsg->type != WDA_REMOVE_STAKEY_RSP) &&
        (limMsg->type != WDA_SET_MIMOPS_RSP)&&
        (limMsg->type != WDA_ADDBA_RSP) &&
        (limMsg->type != WDA_ENTER_BMPS_RSP) &&
        (limMsg->type != WDA_EXIT_BMPS_RSP) &&
        (limMsg->type != WDA_ENTER_IMPS_RSP) &&
        (limMsg->type != WDA_EXIT_IMPS_RSP) &&
        (limMsg->type != WDA_ENTER_UAPSD_RSP) &&
        (limMsg->type != WDA_EXIT_UAPSD_RSP) &&
        (limMsg->type != WDA_WOWL_ENTER_RSP) &&
        (limMsg->type != WDA_WOWL_EXIT_RSP) &&
        (limMsg->type != WDA_SWITCH_CHANNEL_RSP) &&
#ifdef WLAN_FEATURE_P2P 
        (limMsg->type != WDA_P2P_NOA_ATTR_IND) &&
#endif
#ifdef FEATURE_OEM_DATA_SUPPORT
        (limMsg->type != WDA_START_OEM_DATA_RSP) &&
#endif
        (limMsg->type != WDA_ADD_TS_RSP))
    {
        PELOG1(limLog(pMac, LOG1, FL("Defer the current message %s , gLimProcessDefdMsgs is false and system is not in scan/learn mode\n"),
               limMsgStr(limMsg->type));)

        // Defer processsing this message
        if (limDeferMsg(pMac, limMsg) != TX_SUCCESS)
        {
            PELOGE(limLog(pMac, LOGE, FL("Unable to Defer message(0x%X) %s limSmeState %d (prev sme state %d) sysRole %d mlm state %d (prev mlm state %d)\n"),
                   limMsg->type, limMsgStr(limMsg->type), pMac->lim.gLimSmeState,  pMac->lim.gLimPrevSmeState,
                   pMac->lim.gLimSystemRole,  pMac->lim.gLimMlmState,  pMac->lim.gLimPrevMlmState);)
            limLogSessionStates(pMac);
            limHandleDeferMsgError(pMac, limMsg);

        }
        return true;
    }
