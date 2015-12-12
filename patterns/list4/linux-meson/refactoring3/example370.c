switch(interfaceMode)
    {
        case CSR_WIFI_ROUTER_CTRL_MODE_STA:
        case CSR_WIFI_ROUTER_CTRL_MODE_P2PCLI:
            unifi_trace(priv, UDBG4, "mode is STA \n");
            if ((priv->sta_wmm_capabilities & QOS_CAPABILITY_WMM_ENABLED) == 1) {
                priority = uf_get_packet_priority(priv, interfacePriv, skb, proto);
            } else {
                priority = CSR_CONTENTION;
            }
            break;
#ifdef CSR_SUPPORT_SME
        case CSR_WIFI_ROUTER_CTRL_MODE_AP:
        case CSR_WIFI_ROUTER_CTRL_MODE_P2PGO:
        case CSR_WIFI_ROUTER_CTRL_MODE_IBSS:
            {
                CsrWifiRouterCtrlStaInfo_t * dstStaInfo =
                    CsrWifiRouterCtrlGetStationRecordFromPeerMacAddress(priv,ehdr->h_dest, interfacePriv->InterfaceTag);
                unifi_trace(priv, UDBG4, "mode is AP \n");
                if (!(ehdr->h_dest[0] & 0x01) && dstStaInfo && dstStaInfo->wmmOrQosEnabled) {
                    /* If packet is not Broadcast/multicast */
                    priority = uf_get_packet_priority(priv, interfacePriv, skb, proto);
                } else {
                    /* Since packet destination is not QSTA, set priority to CSR_CONTENTION */
                    unifi_trace(priv, UDBG4, "Destination is not QSTA or BroadCast/Multicast\n");
                    priority = CSR_CONTENTION;
                }
            }
            break;
#endif
        default:
            unifi_trace(priv, UDBG3, " mode unknown in %s func, mode=%x\n", __FUNCTION__, interfaceMode);
    }
