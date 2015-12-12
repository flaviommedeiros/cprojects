if (((isMcastPkt) && (priv->wapi_multicast_filter == 1))
#ifdef CSR_WIFI_SECURITY_WAPI_SW_ENCRYPTION
                           || ((!isMcastPkt) && (priv->wapi_unicast_filter == 1))
#endif
                          )
                        {
                            unifi_trace(priv, UDBG4, "Sending the WAPI MPDU for MIC check\n");
                            CsrWifiRouterCtrlWapiRxMicCheckIndSend(priv->CSR_WIFI_SME_IFACEQUEUE, 0, interfaceTag, siglen, sigdata, bulkdata->d[0].data_length, (u8*)bulkdata->d[0].os_data_ptr);

                            for (i = 0; i < UNIFI_MAX_DATA_REFERENCES; i++) {
                                if (bulkdata->d[i].data_length != 0) {
                                    unifi_net_data_free(priv, (void *)&bulkdata->d[i]);
                                }
                           }
                           return;
                       }
