#ifdef WLAN_SOFTAP_FEATURE
if ((psessionEntry->limSystemRole == eLIM_AP_ROLE))
                {
                  
                    if ( (psessionEntry->APWPSIEs.SirWPSProbeRspIE.FieldPresent &
                                               SIR_WPS_PROBRSP_VER_PRESENT) &&
                         (probeReq.wscIePresent ==  1) &&
                         (probeReq.probeReqWscIeInfo.DevicePasswordID.id == 
                                                  WSC_PASSWD_ID_PUSH_BUTTON) &&
                         (probeReq.probeReqWscIeInfo.UUID_E.present == 1))
                    {
                        if(psessionEntry->fwdWPSPBCProbeReq)
                        {
                            PELOG4(sirDumpBuf(pMac, SIR_LIM_MODULE_ID, LOG4,
                                              pHdr->sa, sizeof(tSirMacAddr));)
                            PELOG4(sirDumpBuf(pMac, SIR_LIM_MODULE_ID, LOG4, pBody, frameLen);)
                            limSendSmeProbeReqInd(pMac, pHdr->sa, pBody, frameLen, psessionEntry);
                        } 
                        else
                        {
                            limUpdatePBCSessionEntry(pMac,
                                pHdr->sa, probeReq.probeReqWscIeInfo.UUID_E.uuid, psessionEntry);
                        }
                    }
                }
                else
                {
#endif
                    if (wlan_cfgGetInt(pMac, (tANI_U16) WNI_CFG_WPS_ENABLE, &tmp) != eSIR_SUCCESS)
                        limLog(pMac, LOGP,"Failed to cfg get id %d\n", WNI_CFG_WPS_ENABLE );

                    wpsApEnable = tmp & WNI_CFG_WPS_ENABLE_AP;
                    if ((wpsApEnable) &&
                        (probeReq.wscIePresent ==  1) &&
                        (probeReq.probeReqWscIeInfo.DevicePasswordID.id == WSC_PASSWD_ID_PUSH_BUTTON))
                    {
                        // send the probe req to WSM when it is from a PBC station 
                        if( eHAL_STATUS_SUCCESS != palAllocateMemory( pMac->hHdd,
                               (void **)&pSirSmeProbeReq, sizeof(tSirSmeProbeReq)))
                        {
                            // Log error
                            limLog(pMac, LOGP,
                               FL("call to palAllocateMemory failed for eWNI_SME_PROBE_REQ\n"));
                            return;
                        }
                        msgQ.type = eWNI_SME_PROBE_REQ;
                        msgQ.bodyval = 0;
                        msgQ.bodyptr = pSirSmeProbeReq;
#if defined(ANI_PRODUCT_TYPE_AP) && defined(ANI_LITTLE_BYTE_ENDIAN)
                        sirStoreU16N((tANI_U8*)&pSirSmeProbeReq->messageType, eWNI_SME_PROBE_REQ);
                        sirStoreU16N((tANI_U8*)&pSirSmeProbeReq->length, sizeof(tSirSmeProbeReq));
#else

                        pSirSmeProbeReq->messageType = eWNI_SME_PROBE_REQ;
                        pSirSmeProbeReq->length = sizeof(tSirSmeProbeReq);
#endif
                        pSirSmeProbeReq->sessionId = psessionEntry->smeSessionId;
                        palCopyMemory( pMac->hHdd, pSirSmeProbeReq->peerMacAddr, pHdr->sa, sizeof(tSirMacAddr));
                        pSirSmeProbeReq->devicePasswdId = probeReq.probeReqWscIeInfo.DevicePasswordID.id;
                        MTRACE(macTraceMsgTx(pMac, psessionEntry->peSessionId, msgQ.type));
                       if (limSysProcessMmhMsgApi(pMac, &msgQ,  ePROT) != eSIR_SUCCESS){
                            PELOG3(limLog(pMac, LOG3, FL("couldnt send the probe req to wsm "));)
                        }
                    }
#ifdef WLAN_SOFTAP_FEATURE
                }
