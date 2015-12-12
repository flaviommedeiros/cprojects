if( (pProfile && CSR_IS_WDS_AP( pProfile ) )
#ifdef WLAN_SOFTAP_FEATURE
                     || (pProfile && CSR_IS_INFRA_AP ( pProfile ))
#endif
                    )
                    {
                        //This can be start right away
                        status = csrRoamIssueConnect(pMac, sessionId, pProfile, NULL, eCsrHddIssued, 
                                                    roamId, eANI_BOOLEAN_FALSE, eANI_BOOLEAN_FALSE);
                        if(!HAL_STATUS_SUCCESS(status))
                        {
                            fCallCallback = eANI_BOOLEAN_TRUE;
                        }
                        break;
                    }
