if ((!freeBulkData) &&
                       (interfacePriv->interfaceMode == CSR_WIFI_ROUTER_CTRL_MODE_STA) &&
                       (receptionStatus == CSR_MICHAEL_MIC_ERROR) &&
                       ((priv->wapi_multicast_filter == 1)
#ifdef CSR_WIFI_SECURITY_WAPI_SW_ENCRYPTION
                         || (priv->wapi_unicast_filter == 1)
#endif
                       ))
                   {
                       CSR_SIGNAL signal;
                       u8 *destAddr;
                       CsrResult res;
                       u16 interfaceTag = 0;
                       u8 isMcastPkt = TRUE;

                       unifi_trace(priv, UDBG6, "Received a WAPI data packet when the Unicast/Multicast filter is set\n");
                       res = read_unpack_signal(sigdata, &signal);
                       if (res) {
                           unifi_error(priv, "Received unknown or corrupted signal (0x%x).\n",
                                       CSR_GET_UINT16_FROM_LITTLE_ENDIAN(sigdata));
                           return;
                       }

                       /* Check if the type of MPDU and the respective filter status*/
                       destAddr = (u8 *) bulkdata->d[0].os_data_ptr + MAC_HEADER_ADDR1_OFFSET;
                       isMcastPkt = (destAddr[0] & 0x01) ? TRUE : FALSE;
                       unifi_trace(priv, UDBG6,
                                   "1.MPDU type: (%s), 2.Multicast filter: (%s), 3. Unicast filter: (%s)\n",
                                   ((isMcastPkt) ? "Multiast":"Unicast"),
                                   ((priv->wapi_multicast_filter) ? "Enabled":"Disabled"),
                                   ((priv->wapi_unicast_filter)  ? "Enabled":"Disabled"));

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
                   }
