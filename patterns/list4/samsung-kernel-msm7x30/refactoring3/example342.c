switch( pCommand->command )
        {
#ifdef WLAN_FEATURE_P2P
            case eSmeCommandRemainOnChannel:
                if (NULL != pCommand->u.remainChlCmd.callback)
                {
                    remainOnChanCallback callback = 
                                            pCommand->u.remainChlCmd.callback;
                    /* process the msg */
                    if( callback )
                    {
                        callback(pMac, pCommand->u.remainChlCmd.callbackCtx, 
                                            eCSR_SCAN_ABORT );
                    }
                }
                smeReleaseCommand( pMac, pCommand );
                break;
#endif
            default:
                smeReleaseCommand( pMac, pCommand );
                break;
        }
