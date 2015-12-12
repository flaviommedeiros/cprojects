if ((proto != ETH_P_PAE)
#ifdef CSR_WIFI_SECURITY_WAPI_ENABLE
            && (proto != ETH_P_WAI)
#endif
       ) {
        /* queues 0 - 3 */
        priority = get_packet_priority(priv, skb, &ehdr, interfacePriv);
        queue = unifi_frame_priority_to_queue(priority);
    } else {
        /* queue 4 */
        queue = UNIFI_TRAFFIC_Q_EAPOL;
    }
