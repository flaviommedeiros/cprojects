if (isWapiUnicastPkt &&
                    ((uf_sme_port_state(priv,srcAddr,UF_CONTROLLED_PORT_Q,interfaceTag) != CSR_WIFI_ROUTER_CTRL_PORT_ACTION_8021X_PORT_OPEN)||
#ifndef CSR_WIFI_SECURITY_WAPI_SW_ENCRYPTION
                    (priv->wapi_unicast_filter) ||
#endif
                    (priv->wapi_unicast_queued_pkt_filter))) {

                    /* Workaround to handle MIC failures reported by the firmware for encrypted packets from the AP
                     * while we are in the process of re-association induced by unsupported WAPI Unicast key index
                     *             - Discard the packets with MIC failures "until" we have
                     *               a. negotiated a key,
                     *               b. opened the CONTROL PORT and
                     *               c. the AP has started using the new key
                     */
                    unifi_trace(priv, UDBG4, "Ignoring the MIC failure as either a. CONTROL PORT isn't OPEN or b. Unicast filter is set or c. WAPI AP using old key for buffered pkts\n");

                    /*Ignore this MIC failure*/
                    return FALSE;

                }
