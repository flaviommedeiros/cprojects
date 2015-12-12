switch ( pCommand->command )
                    {

                        case eSmeCommandScan:
                            csrLLUnlock( &pMac->sme.smeCmdActiveList );
                            status = csrProcessScanCommand( pMac, pCommand );
                            break;

                        case eSmeCommandRoam:
                            csrLLUnlock( &pMac->sme.smeCmdActiveList );
                            status  = csrRoamProcessCommand( pMac, pCommand );
                            break;

                        case eSmeCommandWmStatusChange:
                            csrLLUnlock( &pMac->sme.smeCmdActiveList );
                            csrRoamProcessWmStatusChangeCommand(pMac, pCommand);
                            break;

                        case eSmeCommandSetKey:
                            csrLLUnlock( &pMac->sme.smeCmdActiveList );
                            status = csrRoamProcessSetKeyCommand( pMac, pCommand );
                            if(!HAL_STATUS_SUCCESS(status))
                            {
                                if( csrLLRemoveEntry( &pMac->sme.smeCmdActiveList, 
                                            &pCommand->Link, LL_ACCESS_LOCK ) )
                                {
                                    csrReleaseCommandSetKey( pMac, pCommand );
                                }
                            }
                            break;

                        case eSmeCommandRemoveKey:
                            csrLLUnlock( &pMac->sme.smeCmdActiveList );
                            status = csrRoamProcessRemoveKeyCommand( pMac, pCommand );
                            if(!HAL_STATUS_SUCCESS(status))
                            {
                                if( csrLLRemoveEntry( &pMac->sme.smeCmdActiveList, 
                                            &pCommand->Link, LL_ACCESS_LOCK ) )
                                {
                                    csrReleaseCommandRemoveKey( pMac, pCommand );
                                }
                            }
                            break;

                        case eSmeCommandAddStaSession:
                            csrLLUnlock( &pMac->sme.smeCmdActiveList );
                            csrProcessAddStaSessionCommand( pMac, pCommand );
                            break;
                        case eSmeCommandDelStaSession:    
                            csrLLUnlock( &pMac->sme.smeCmdActiveList );
                            csrProcessDelStaSessionCommand( pMac, pCommand );
                            break;

#ifdef FEATURE_OEM_DATA_SUPPORT
                        case eSmeCommandOemDataReq:
                            csrLLUnlock(&pMac->sme.smeCmdActiveList);
                            oemData_ProcessOemDataReqCommand(pMac, pCommand);
                            break;
#endif
#if defined WLAN_FEATURE_P2P
                        case eSmeCommandRemainOnChannel:
                            csrLLUnlock(&pMac->sme.smeCmdActiveList);
                            p2pProcessRemainOnChannelCmd(pMac, pCommand);
                            break;
                        case eSmeCommandNoAUpdate:
                            csrLLUnlock( &pMac->sme.smeCmdActiveList );
                            p2pProcessNoAReq(pMac,pCommand);
#endif
                        case eSmeCommandEnterImps:
                        case eSmeCommandExitImps:
                        case eSmeCommandEnterBmps:
                        case eSmeCommandExitBmps:
                        case eSmeCommandEnterUapsd:
                        case eSmeCommandExitUapsd:
                        case eSmeCommandEnterWowl:
                        case eSmeCommandExitWowl:
                            csrLLUnlock( &pMac->sme.smeCmdActiveList );
                            fContinue = pmcProcessCommand( pMac, pCommand );
                            if( fContinue )
                            {
                                //The command failed, remove it
                                if( csrLLRemoveEntry( &pMac->sme.smeCmdActiveList,
                                            &pCommand->Link, LL_ACCESS_LOCK ) )
                                {
                                    pmcReleaseCommand( pMac, pCommand );
                                }
                            }
                            break;

                        //Treat standby differently here because caller may not be able to handle
                        //the failure so we do our best here
                        case eSmeCommandEnterStandby:
                            if( csrIsConnStateDisconnected( pMac, pCommand->sessionId ) )
                            {
                                //It can continue
                                csrLLUnlock( &pMac->sme.smeCmdActiveList );
                                fContinue = pmcProcessCommand( pMac, pCommand );
                                if( fContinue )
                                {
                                    //The command failed, remove it
                                    if( csrLLRemoveEntry( &pMac->sme.smeCmdActiveList,
                                                &pCommand->Link, LL_ACCESS_LOCK ) )
                                    {
                                        pmcReleaseCommand( pMac, pCommand );
                                    }
                                }
                            }
                            else
                            {
                                //Need to issue a disconnect first before processing this command
                                tSmeCmd *pNewCmd;

                                //We need to re-run the command
                                fContinue = eANI_BOOLEAN_TRUE;
                                //Pull off the standby command first
                                if( csrLLRemoveEntry( &pMac->sme.smeCmdActiveList,
                                                &pCommand->Link, LL_ACCESS_NOLOCK ) )
                                {
                                    csrLLUnlock( &pMac->sme.smeCmdActiveList );
                                    //Need to call CSR function here because the disconnect command
                                    //is handled by CSR
                                    pNewCmd = csrGetCommandBuffer( pMac );
                                    if( NULL != pNewCmd )
                                    {
                                        //Put the standby command to the head of the pending list first
                                        csrLLInsertHead( &pMac->sme.smeCmdPendingList, &pCommand->Link,
                                                        LL_ACCESS_LOCK );
                                        pNewCmd->command = eSmeCommandRoam;
                                        pNewCmd->u.roamCmd.roamReason = eCsrForcedDisassoc;
                                        //Put the disassoc command before the standby command
                                        csrLLInsertHead( &pMac->sme.smeCmdPendingList, &pNewCmd->Link,
                                                        LL_ACCESS_LOCK );
                                    }
                                    else
                                    {
                                        //Continue the command here
                                        fContinue = pmcProcessCommand( pMac, pCommand );
                                        if( fContinue )
                                        {
                                            //The command failed, remove it
                                            if( csrLLRemoveEntry( &pMac->sme.smeCmdActiveList,
                                                        &pCommand->Link, LL_ACCESS_LOCK ) )
                                            {
                                                pmcReleaseCommand( pMac, pCommand );
                                            }
                                        }
                                    }
                                }
                                else
                                {
                                    csrLLUnlock( &pMac->sme.smeCmdActiveList );
                                    smsLog( pMac, LOGE, FL(" failed to remove standby command\n") );
                                    VOS_ASSERT(0);
                                }
                            }
                            break;

                        case eSmeCommandAddTs:
                        case eSmeCommandDelTs:
                            csrLLUnlock( &pMac->sme.smeCmdActiveList );
#ifndef WLAN_MDM_CODE_REDUCTION_OPT
                            fContinue = qosProcessCommand( pMac, pCommand );
                            if( fContinue )
                            {
                                //The command failed, remove it
                                if( csrLLRemoveEntry( &pMac->sme.smeCmdActiveList,
                                            &pCommand->Link, LL_ACCESS_NOLOCK ) )
                                {
//#ifndef WLAN_MDM_CODE_REDUCTION_OPT
                                    qosReleaseCommand( pMac, pCommand );
//#endif /* WLAN_MDM_CODE_REDUCTION_OPT*/
                                }
                            }
#endif
                            break;

                        default:
                            //something is wrong
                            //remove it from the active list
                            smsLog(pMac, LOGE, " csrProcessCommand processes an unknown command %d\n", pCommand->command);
                            pEntry = csrLLRemoveHead( &pMac->sme.smeCmdActiveList, LL_ACCESS_NOLOCK );
                            csrLLUnlock( &pMac->sme.smeCmdActiveList );
                            pCommand = GET_BASE_ADDR( pEntry, tSmeCmd, Link );
                            smeReleaseCommand( pMac, pCommand );
                            status = eHAL_STATUS_FAILURE;
                            break;
                    }
