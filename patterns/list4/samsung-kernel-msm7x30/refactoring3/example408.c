switch (msg.type & 0xFF00)
        {
            case SIR_HAL_MSG_TYPES_BEGIN:
                if (halPostMsgApi(pMac, &msg) != eSIR_SUCCESS)
                    sysLog(pMac, LOGP, "sysMmhEntry: halPostMsgApi Failed!\n");
                else
                {
                    sysLog(pMac, LOG4, "<MMH> Message forwarded to HAL\n");
                }

                break;

            case SIR_LIM_MSG_TYPES_BEGIN:
                limPostMsgApi(pMac, &msg);
                break;

            case SIR_MNT_MSG_TYPES_BEGIN:

                if (halMntPostMsgApi(pMac, &msg) != eSIR_SUCCESS)
                    sysLog(pMac, LOGP, "sysMmhEntry: halMntPostMsgApi Failed!\n");
                else
                {
                    sysLog(pMac, LOG4, "<MMH> Message forwarded to MNT type (%X)\n",
                           msg.type);
                }

                break;

            case SIR_PMM_MSG_TYPES_BEGIN:

                // Shall have its API call here; Once API is added, remove the
                // following release memory call.
                break;

            case SIR_CFG_MSG_TYPES_BEGIN:

                if (halMntPostMsgApi(pMac, &msg) != eSIR_SUCCESS)
                    sysLog(pMac, LOGP,
                           "sysMmhEntry: cfg msg: halMntPostMsgApi Failed!\n");
                else
                {
                    sysLog(pMac, LOG4,
                           "sysMmhEntry: cfg msg: halMntPostMsgApi!\n");
                }

                break;

#ifndef WLAN_FTM_STUB
            case PTT_MSG_TYPES_BEGIN_30: /*PTT_MSG_TYPES_BEGIN:*/
            case PTT_MSG_TYPES_BEGIN_31:
            case PTT_MSG_TYPES_BEGIN_32:
                if (postPTTMsgApi(pMac, &msg) != eSIR_SUCCESS)
                    sysLog(pMac, LOGP,
                           "sysMmhEntry: RD msg: postPTTMsgApi Failed!\n");
                else
                {
                    sysLog(pMac, LOG4,
                           "sysMmhEntry: RD msg: postPTTMsgApi!\n");
                }
                break;
#endif

            default:
                sysLog(pMac, LOGW, "sysMmhEntry Unknown destination \n");
                // Unknown destination.  Just drop it
                palFreeMemory( pMac->hHdd, (void*)pMbMsg);
        }
