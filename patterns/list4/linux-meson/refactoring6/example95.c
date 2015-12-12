if ((proto != ETH_P_PAE)
#ifdef CSR_WIFI_SECURITY_WAPI_ENABLE
            && (proto != ETH_P_WAI)
#endif
       ) {
        port = UF_CONTROLLED_PORT_Q;
    } else {
        /* queue 4 */
        port = UF_UNCONTROLLED_PORT_Q;
    }
