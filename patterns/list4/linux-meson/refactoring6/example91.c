if((snap_protocol == ETH_P_PAE)
#ifdef CSR_WIFI_SECURITY_WAPI_ENABLE
       || (snap_protocol == ETH_P_WAI)
#endif
    )
    {
        queue = UF_UNCONTROLLED_PORT_Q;
    }
    else
    {
        queue = UF_CONTROLLED_PORT_Q;
    }
