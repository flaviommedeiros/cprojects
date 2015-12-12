switch (msgType)
    {
        case LIM_MLM_SCAN_CNF:
            limProcessMlmScanCnf(pMac, pMsgBuf);
            break;

#ifdef FEATURE_OEM_DATA_SUPPORT
        case LIM_MLM_OEM_DATA_CNF:
            limProcessMlmOemDataReqCnf(pMac, pMsgBuf);
            break;
#endif

        case LIM_MLM_AUTH_CNF:
            limProcessMlmAuthCnf(pMac, pMsgBuf);
            break;
        case LIM_MLM_AUTH_IND:
            limProcessMlmAuthInd(pMac, pMsgBuf);
            break;
        case LIM_MLM_ASSOC_CNF:
            limProcessMlmAssocCnf(pMac, pMsgBuf);
            break;
        case LIM_MLM_START_CNF:
            limProcessMlmStartCnf(pMac, pMsgBuf);
            break;
        case LIM_MLM_JOIN_CNF:
            limProcessMlmJoinCnf(pMac, pMsgBuf);
            break;
        case LIM_MLM_ASSOC_IND:
             limProcessMlmAssocInd(pMac, pMsgBuf);
            break;
        case LIM_MLM_REASSOC_CNF:
            limProcessMlmReassocCnf(pMac, pMsgBuf);
            break;
        case LIM_MLM_REASSOC_IND:
           limProcessMlmReassocInd(pMac, pMsgBuf);
           break;
        case LIM_MLM_DISASSOC_CNF:
            limProcessMlmDisassocCnf(pMac, pMsgBuf);
            break;
        case LIM_MLM_DISASSOC_IND:
            limProcessMlmDisassocInd(pMac, pMsgBuf);
            break;
        case LIM_MLM_PURGE_STA_IND:
            limProcessMlmPurgeStaInd(pMac, pMsgBuf);
            break;
        case LIM_MLM_DEAUTH_CNF:
            limProcessMlmDeauthCnf(pMac, pMsgBuf);
            break;
        case LIM_MLM_DEAUTH_IND:
            limProcessMlmDeauthInd(pMac, pMsgBuf);
            break;
        case LIM_MLM_SETKEYS_CNF:
            limProcessMlmSetKeysCnf(pMac, pMsgBuf);
            break;
        case LIM_MLM_REMOVEKEY_CNF:
            limProcessMlmRemoveKeyCnf(pMac, pMsgBuf);
            break;
        case LIM_MLM_TSPEC_CNF:
            break;
        case LIM_MLM_ADDBA_CNF:
            limProcessMlmAddBACnf( pMac, pMsgBuf );
            break;
        case LIM_MLM_DELBA_CNF:
            limProcessMlmDelBACnf( pMac, pMsgBuf );
            break;
        default:
            break;
    }
