#ifdef CSR_WIFI_SECURITY_WAPI_ENABLE
if (proto == ETH_P_WAI)
     {
        protection = 0; /*WAI packets always sent unencrypted*/
     }
   else
     {
#endif
#ifdef CSR_SUPPORT_SME
    if ((protection = uf_get_protection_bit_from_interfacemode(priv, interfaceTag, ehdr->h_dest)) < 0) {
        unifi_warning(priv, "unicast address, but destination not in station record database\n");
        unifi_net_data_free(priv, &bulkdata.d[0]);
        return -1;
    }
#else
    protection = 0;
#endif
#ifdef CSR_WIFI_SECURITY_WAPI_ENABLE
   }
