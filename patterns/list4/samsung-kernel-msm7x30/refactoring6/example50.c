if(((0 == pScanCmd->u.scanCmd.scanID)
                   && (eCSR_SCAN_REQUEST_11D_SCAN != pScanRequest->requestType))
#ifdef SOFTAP_CHANNEL_RANGE
                   && (eCSR_SCAN_SOFTAP_CHANNEL_RANGE != pScanRequest->requestType)
#endif                   
                   && (eANI_BOOLEAN_FALSE == pMac->scan.fEnableBypass11d)
                   )
                {
                    tSmeCmd *p11dScanCmd;
                    tCsrScanRequest scanReq;
                    tCsrChannelInfo *pChnInfo = &scanReq.ChannelInfo;

                    palZeroMemory(pMac->hHdd, &scanReq, sizeof(tCsrScanRequest));

                    p11dScanCmd = csrGetCommandBuffer(pMac);
                    if(p11dScanCmd)
                    {
                        tANI_U32 numChn = pMac->scan.baseChannels.numChannels;

                        palZeroMemory(pMac->hHdd, &p11dScanCmd->u.scanCmd, sizeof(tScanCmd));
                        status = palAllocateMemory( pMac->hHdd, (void **)&pChnInfo->ChannelList, numChn );
                        if( !HAL_STATUS_SUCCESS( status ) )
                        {
                            break;
                        }
                        status = palCopyMemory( pMac->hHdd, pChnInfo->ChannelList, 
                                    pMac->scan.baseChannels.channelList, numChn );
                        if( !HAL_STATUS_SUCCESS( status ) )
                        {
                            palFreeMemory( pMac->hHdd, pChnInfo->ChannelList );
                            pChnInfo->ChannelList = NULL;
                            break;
                        }
                        pChnInfo->numOfChannels = (tANI_U8)numChn;
                        p11dScanCmd->command = eSmeCommandScan;
                        p11dScanCmd->u.scanCmd.callback = NULL;
                        p11dScanCmd->u.scanCmd.pContext = NULL;
                        p11dScanCmd->u.scanCmd.scanID = pMac->scan.nextScanID++;                
                        scanReq.BSSType = eCSR_BSS_TYPE_ANY;

                        if ( csrIs11dSupported(pMac) )
                        {
                            scanReq.scanType = eSIR_PASSIVE_SCAN;
                            scanReq.requestType = eCSR_SCAN_REQUEST_11D_SCAN;
                            p11dScanCmd->u.scanCmd.reason = eCsrScan11d1;
                            scanReq.maxChnTime = pMac->roam.configParam.nPassiveMaxChnTime;
                            scanReq.minChnTime = pMac->roam.configParam.nPassiveMinChnTime;
                        }
                        else
                        {
                            scanReq.scanType = eSIR_ACTIVE_SCAN;
                            scanReq.requestType = eCSR_SCAN_IDLE_MODE_SCAN;
                            p11dScanCmd->u.scanCmd.reason = eCsrScanIdleScan;
                            scanReq.maxChnTime = pMac->roam.configParam.nActiveMaxChnTime;
                            scanReq.minChnTime = pMac->roam.configParam.nActiveMinChnTime;
                        }

                        status = csrScanCopyRequest(pMac, &p11dScanCmd->u.scanCmd.u.scanRequest, &scanReq);
                        //Free the channel list
                        palFreeMemory( pMac->hHdd, pChnInfo->ChannelList );

                        if(HAL_STATUS_SUCCESS(status))
                        {
                            //Start process the command
#ifdef WLAN_AP_STA_CONCURRENCY
                            status = csrQueueScanRequest(pMac, p11dScanCmd);
#else
                            status = csrQueueSmeCommand(pMac, p11dScanCmd, eANI_BOOLEAN_FALSE);
#endif                   
                            if( !HAL_STATUS_SUCCESS( status ) )
                            {
                                smsLog( pMac, LOGE, FL(" fail to send message status = %d\n"), status );
                                break;
                            }
                        }
                        else 
                        {
                            break;
                        }
                    }
                    else
                    {
                        //error
                        break;
                    }
                }
