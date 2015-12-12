if ((proto == ETH_P_PAE)
#ifdef CSR_WIFI_SECURITY_WAPI_ENABLE
            || (proto == ETH_P_WAI)
#endif
       )
    {
        /* check for m4 detection */
        if (0 == uf_verify_m4(priv, bulkdata.d[0].os_data_ptr, bulkdata.d[0].data_length)) {
            eapolStore = TRUE;
        }
    }
