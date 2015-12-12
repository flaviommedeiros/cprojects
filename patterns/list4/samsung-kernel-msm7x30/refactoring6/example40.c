if((eCSR_AUTH_TYPE_RSN == authType) ||
#if defined WLAN_FEATURE_VOWIFI_11R
                (eCSR_AUTH_TYPE_FT_RSN == authType) ||
                (eCSR_AUTH_TYPE_FT_RSN_PSK == authType) ||
#endif /* WLAN_FEATURE_VOWIFI_11R */
                (eCSR_AUTH_TYPE_RSN_PSK == authType))
            {
                if(pIesLocal->RSN.present)
                {
                    //Calculate the actual length
                    nIeLen = 8 //version + gp_cipher_suite + pwise_cipher_suite_count
                        + pIesLocal->RSN.pwise_cipher_suite_count * 4    //pwise_cipher_suites
                        + 2 //akm_suite_count
                        + pIesLocal->RSN.akm_suite_count * 4 //akm_suites
                        + 2; //reserved
                    if( pIesLocal->RSN.pmkid_count )
                    {
                        nIeLen += 2 + pIesLocal->RSN.pmkid_count * 4;  //pmkid
                    }
                    //nIeLen doesn't count EID and length fields
                    if(HAL_STATUS_SUCCESS((status = palAllocateMemory(pMac->hHdd, (void **)&pSession->pWpaRsnRspIE, nIeLen + 2))))
                    {
                        pSession->pWpaRsnRspIE[0] = DOT11F_EID_RSN;
                        pSession->pWpaRsnRspIE[1] = (tANI_U8)nIeLen;
                        //copy upto akm_suites
                        pIeBuf = pSession->pWpaRsnRspIE + 2;
                        palCopyMemory(pMac->hHdd, pIeBuf, &pIesLocal->RSN.version, 8);
                        pIeBuf += 8;
                        if( pIesLocal->RSN.pwise_cipher_suite_count )
                        {
                            //copy pwise_cipher_suites
                            palCopyMemory(pMac->hHdd, pIeBuf, pIesLocal->RSN.pwise_cipher_suites, 
                                            pIesLocal->RSN.pwise_cipher_suite_count * 4);
                            pIeBuf += pIesLocal->RSN.pwise_cipher_suite_count * 4;
                        }
                        palCopyMemory(pMac->hHdd, pIeBuf, &pIesLocal->RSN.akm_suite_count, 2);
                        pIeBuf += 2;
                        if( pIesLocal->RSN.akm_suite_count )
                        {
                            //copy akm_suites
                            palCopyMemory(pMac->hHdd, pIeBuf, pIesLocal->RSN.akm_suites, 
                                            pIesLocal->RSN.akm_suite_count * 4);
                            pIeBuf += pIesLocal->RSN.akm_suite_count * 4;
                        }
                        //copy the rest
                        palCopyMemory(pMac->hHdd, pIeBuf, pIesLocal->RSN.akm_suites + 
                                        pIesLocal->RSN.akm_suite_count * 4, 
                                        2 + pIesLocal->RSN.pmkid_count * 4);
                        pSession->nWpaRsnRspIeLength = nIeLen + 2; 
                    }
                }
            }
            else if((eCSR_AUTH_TYPE_WPA == authType) ||
                (eCSR_AUTH_TYPE_WPA_PSK == authType))
            {
                if(pIesLocal->WPA.present)
                {
                    //Calculate the actual length
                    nIeLen = 12 //OUI + version + multicast_cipher + unicast_cipher_count
                        + pIesLocal->WPA.unicast_cipher_count * 4    //unicast_ciphers
                        + 2 //auth_suite_count
                        + pIesLocal->WPA.auth_suite_count * 4; //auth_suites
                    // The WPA capabilities follows the Auth Suite (two octects)--
                    // this field is optional, and we always "send" zero, so just
                    // remove it.  This is consistent with our assumptions in the
                    // frames compiler; c.f. bug 15234:
                    //nIeLen doesn't count EID and length fields
                    if(HAL_STATUS_SUCCESS((status = palAllocateMemory(pMac->hHdd, (void **)&pSession->pWpaRsnRspIE, nIeLen + 2))))
                    {
                        pSession->pWpaRsnRspIE[0] = DOT11F_EID_WPA;
                        pSession->pWpaRsnRspIE[1] = (tANI_U8)nIeLen;
                        pIeBuf = pSession->pWpaRsnRspIE + 2;
                        //Copy WPA OUI
                        palCopyMemory(pMac->hHdd, pIeBuf, &csrWpaOui[1], 4);
                        pIeBuf += 4;
                        palCopyMemory(pMac->hHdd, pIeBuf, &pIesLocal->WPA.version, 8 + 
                                        pIesLocal->WPA.unicast_cipher_count * 4);
                        pIeBuf += 8 + pIesLocal->WPA.unicast_cipher_count * 4;
                        palCopyMemory(pMac->hHdd, pIeBuf, &pIesLocal->WPA.auth_suite_count, 2 + 
                                        pIesLocal->WPA.auth_suite_count * 4);
                        pIeBuf += pIesLocal->WPA.auth_suite_count * 4;
                        pSession->nWpaRsnRspIeLength = nIeLen + 2; 
                    }
                }
            }
#ifdef FEATURE_WLAN_WAPI
          else if((eCSR_AUTH_TYPE_WAPI_WAI_PSK == authType) ||
                  (eCSR_AUTH_TYPE_WAPI_WAI_CERTIFICATE == authType))
          {
                if(pIesLocal->WAPI.present)
                {
                   //Calculate the actual length
                   nIeLen = 4 //version + akm_suite_count 
                      + pIesLocal->WAPI.akm_suite_count * 4 // akm_suites
                      + 2 //pwise_cipher_suite_count
                      + pIesLocal->WAPI.unicast_cipher_suite_count * 4    //pwise_cipher_suites
                      + 6; //gp_cipher_suite + preauth + reserved
                      if( pIesLocal->WAPI.bkid_count )
                      {
                           nIeLen += 2 + pIesLocal->WAPI.bkid_count * 4;  //bkid
        }
                      
                   //nIeLen doesn't count EID and length fields
                   if(HAL_STATUS_SUCCESS((status = palAllocateMemory(pMac->hHdd, (void **)&pSession->pWapiRspIE, nIeLen + 2))))
                   {
                      pSession->pWapiRspIE[0] = DOT11F_EID_WAPI;
                      pSession->pWapiRspIE[1] = (tANI_U8)nIeLen;
                      pIeBuf = pSession->pWapiRspIE + 2;
                      //copy upto akm_suite_count
                      palCopyMemory(pMac->hHdd, pIeBuf, &pIesLocal->WAPI.version, 4);
                      pIeBuf += 4;
                      if( pIesLocal->WAPI.akm_suite_count )
                      {
                         //copy akm_suites
                         palCopyMemory(pMac->hHdd, pIeBuf, pIesLocal->WAPI.akm_suites, 
                                        pIesLocal->WAPI.akm_suite_count * 4);
                         pIeBuf += pIesLocal->WAPI.akm_suite_count * 4;
    }
                      palCopyMemory(pMac->hHdd, pIeBuf, &pIesLocal->WAPI.unicast_cipher_suite_count, 2);
                      pIeBuf += 2;
                      if( pIesLocal->WAPI.unicast_cipher_suite_count )
                      {
                         //copy pwise_cipher_suites
                         palCopyMemory(pMac->hHdd, pIeBuf, pIesLocal->WAPI.unicast_cipher_suites, 
                                        pIesLocal->WAPI.unicast_cipher_suite_count * 4);
                         pIeBuf += pIesLocal->WAPI.unicast_cipher_suite_count * 4;
                      }
                      //gp_cipher_suite + preauth + reserved + bkid_count
                      palCopyMemory(pMac->hHdd, pIeBuf, &pIesLocal->WAPI.multicast_cipher_suite, 8);
                      pIeBuf += 8;
                      if( pIesLocal->WAPI.bkid_count )
                      {
                         //copy akm_suites
                         palCopyMemory(pMac->hHdd, pIeBuf, pIesLocal->WAPI.bkid, pIesLocal->WAPI.bkid_count * 4);
                         pIeBuf += pIesLocal->WAPI.bkid_count * 4;
                      }
                      pSession->nWapiRspIeLength = nIeLen + 2; 
                   }
                }
          }
