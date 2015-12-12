switch ( elementId ) 
        {
            case DOT11F_EID_WPA: 
                if ((2+4) > eLen) /* should have at least OUI */
                {
                    hddLog(VOS_TRACE_LEVEL_ERROR, 
                              "%s: Invalid WPA IE", __func__);
                    return -EINVAL;
                }
                else if (0 == memcmp(&genie[0], "\x00\x50\xf2\x04", 4)) 
                {
                    v_U16_t curAddIELen = pWextState->assocAddIE.length;
                    hddLog (VOS_TRACE_LEVEL_INFO, "%s Set WPS IE(len %d)", 
                            __func__, eLen + 2);
                    
                    if( SIR_MAC_MAX_IE_LENGTH < (pWextState->assocAddIE.length + eLen) )
                    {
                       hddLog(VOS_TRACE_LEVEL_FATAL, "Cannot accomadate assocAddIE. "
                                                      "Need bigger buffer space\n");
                       VOS_ASSERT(0);
                       return -ENOMEM;
                    }
                    // WSC IE is saved to Additional IE ; it should be accumulated to handle WPS IE + P2P IE
                    memcpy( pWextState->assocAddIE.addIEdata + curAddIELen, genie - 2, eLen + 2);
                    pWextState->assocAddIE.length += eLen + 2;
                    
                    pWextState->roamProfile.bWPSAssociation = VOS_TRUE;
                    pWextState->roamProfile.pAddIEAssoc = pWextState->assocAddIE.addIEdata;
                    pWextState->roamProfile.nAddIEAssocLength = pWextState->assocAddIE.length;
                }
                else if (0 == memcmp(&genie[0], "\x00\x50\xf2", 3)) 
                {  
                    hddLog (VOS_TRACE_LEVEL_INFO, "%s Set WPA IE (len %d)",__func__, eLen + 2);
                    memset( pWextState->WPARSNIE, 0, MAX_WPA_RSN_IE_LEN );
                    memcpy( pWextState->WPARSNIE, genie - 2, (eLen + 2) /*ie_len*/);
                    pWextState->roamProfile.pWPAReqIE = pWextState->WPARSNIE;
                    pWextState->roamProfile.nWPAReqIELength = eLen + 2;//ie_len;
                }
#ifdef WLAN_FEATURE_P2P
                else if ( (0 == memcmp(&genie[0], P2P_OUI_TYPE, 
                                                         P2P_OUI_TYPE_SIZE)) 
                        /*Consider P2P IE, only for P2P Client */
                         && (WLAN_HDD_P2P_CLIENT == pAdapter->device_mode) )
                {
                    v_U16_t curAddIELen = pWextState->assocAddIE.length;
                    hddLog (VOS_TRACE_LEVEL_INFO, "%s Set P2P IE(len %d)", 
                            __func__, eLen + 2);
                    
                    if( SIR_MAC_MAX_IE_LENGTH < (pWextState->assocAddIE.length + eLen) )
                    {
                       hddLog(VOS_TRACE_LEVEL_FATAL, "Cannot accomadate assocAddIE "
                                                      "Need bigger buffer space\n");
                       VOS_ASSERT(0);
                       return -ENOMEM;
                    }
                    // P2P IE is saved to Additional IE ; it should be accumulated to handle WPS IE + P2P IE
                    memcpy( pWextState->assocAddIE.addIEdata + curAddIELen, genie - 2, eLen + 2);
                    pWextState->assocAddIE.length += eLen + 2;
                    
                    pWextState->roamProfile.pAddIEAssoc = pWextState->assocAddIE.addIEdata;
                    pWextState->roamProfile.nAddIEAssocLength = pWextState->assocAddIE.length;
                }
#endif
#ifdef WLAN_FEATURE_WFD
                else if ( (0 == memcmp(&genie[0], WFD_OUI_TYPE, 
                                                         WFD_OUI_TYPE_SIZE)) 
                        /*Consider WFD IE, only for P2P Client */
                         && (WLAN_HDD_P2P_CLIENT == pAdapter->device_mode) )
                {
                    v_U16_t curAddIELen = pWextState->assocAddIE.length;
                    hddLog (VOS_TRACE_LEVEL_INFO, "%s Set WFD IE(len %d)", 
                            __func__, eLen + 2);
                    
                    if( SIR_MAC_MAX_IE_LENGTH < (pWextState->assocAddIE.length + eLen) )
                    {
                       hddLog(VOS_TRACE_LEVEL_FATAL, "Cannot accomadate assocAddIE "
                                                      "Need bigger buffer space\n");
                       VOS_ASSERT(0);
                       return -ENOMEM;
                    }
                    // WFD IE is saved to Additional IE ; it should be accumulated to handle
                    // WPS IE + P2P IE + WFD IE
                    memcpy( pWextState->assocAddIE.addIEdata + curAddIELen, genie - 2, eLen + 2);
                    pWextState->assocAddIE.length += eLen + 2;
                    
                    pWextState->roamProfile.pAddIEAssoc = pWextState->assocAddIE.addIEdata;
                    pWextState->roamProfile.nAddIEAssocLength = pWextState->assocAddIE.length;
                }
#endif
                break;
            case DOT11F_EID_RSN:
                hddLog (VOS_TRACE_LEVEL_INFO, "%s Set RSN IE(len %d)",__func__, eLen + 2);
                memset( pWextState->WPARSNIE, 0, MAX_WPA_RSN_IE_LEN );
                memcpy( pWextState->WPARSNIE, genie - 2, (eLen + 2)/*ie_len*/);
                pWextState->roamProfile.pRSNReqIE = pWextState->WPARSNIE;
                pWextState->roamProfile.nRSNReqIELength = eLen + 2; //ie_len;
                break;
#ifdef FEATURE_WLAN_WAPI
            case WLAN_EID_WAPI:
                pAdapter->wapi_info.nWapiMode = 1;   //Setting WAPI Mode to ON=1
                hddLog(VOS_TRACE_LEVEL_INFO,"WAPI MODE IS  %lu \n",
                                          pAdapter->wapi_info.nWapiMode);
                tmp = (u16 *)ie;
                tmp = tmp + 2; // Skip element Id and Len, Version        
                akmsuiteCount = WPA_GET_LE16(tmp);
                tmp = tmp + 1;
                akmlist = (int *)(tmp);
                if(akmsuiteCount <= MAX_NUM_AKM_SUITES)
                {
                    memcpy(akmsuite, akmlist, (4*akmsuiteCount));
                }
                else
                {
                    hddLog(VOS_TRACE_LEVEL_FATAL, "Invalid akmSuite count\n");
                    VOS_ASSERT(0);
                    return -EINVAL;
                }

                if (WAPI_PSK_AKM_SUITE == akmsuite[0])
                {
                    hddLog(VOS_TRACE_LEVEL_INFO, "%s: WAPI AUTH MODE SET TO PSK",
                                                            __FUNCTION__);
                    pAdapter->wapi_info.wapiAuthMode = WAPI_AUTH_MODE_PSK;
                }    
                if (WAPI_CERT_AKM_SUITE == akmsuite[0])
                {     
                    hddLog(VOS_TRACE_LEVEL_INFO, "%s: WAPI AUTH MODE SET TO CERTIFICATE",
                                                             __FUNCTION__);
                    pAdapter->wapi_info.wapiAuthMode = WAPI_AUTH_MODE_CERT;
                }
                break;
#endif
            default:
                hddLog (VOS_TRACE_LEVEL_ERROR, 
                        "%s Set UNKNOWN IE %X", __func__, elementId);
                return 0;
        }
