switch (params->cipher) 
    {
        case WLAN_CIPHER_SUITE_WEP40:
            setKey.encType = eCSR_ENCRYPT_TYPE_WEP40_STATICKEY;
            break;

        case WLAN_CIPHER_SUITE_WEP104:
            setKey.encType = eCSR_ENCRYPT_TYPE_WEP104_STATICKEY;
            break;

        case WLAN_CIPHER_SUITE_TKIP:
            {
                u8 *pKey = &setKey.Key[0];
                setKey.encType = eCSR_ENCRYPT_TYPE_TKIP;

                vos_mem_zero(pKey, CSR_MAX_KEY_LEN);

                /*Supplicant sends the 32bytes key in this order 

                  |--------------|----------|----------|
                  |   Tk1        |TX-MIC    |  RX Mic  | 
                  |--------------|----------|----------|
                  <---16bytes---><--8bytes--><--8bytes-->

                */
                /*Sme expects the 32 bytes key to be in the below order

                  |--------------|----------|----------|
                  |   Tk1        |RX-MIC    |  TX Mic  | 
                  |--------------|----------|----------|
                  <---16bytes---><--8bytes--><--8bytes-->
                  */
                /* Copy the Temporal Key 1 (TK1) */
                vos_mem_copy(pKey, params->key,16);

                /*Copy the rx mic first*/
                vos_mem_copy(&pKey[16],&params->key[24],8); 

                /*Copy the tx mic */
                vos_mem_copy(&pKey[24],&params->key[16],8); 


                break;
            }

        case WLAN_CIPHER_SUITE_CCMP:
            setKey.encType = eCSR_ENCRYPT_TYPE_AES;
            break;

#ifdef FEATURE_WLAN_WAPI
        case WLAN_CIPHER_SUITE_SMS4:
            {
                vos_mem_zero(&setKey,sizeof(tCsrRoamSetKey));
                wlan_hdd_cfg80211_set_key_wapi(pAdapter, key_index, mac_addr,
                        params->key, params->key_len);
                return 0;
            }
#endif
#ifdef FEATURE_WLAN_CCX
        case WLAN_CIPHER_SUITE_KRK:
            setKey.encType = eCSR_ENCRYPT_TYPE_KRK;
            break;
#endif
        default:
            hddLog(VOS_TRACE_LEVEL_ERROR, "%s: unsupported cipher type %lu",
                    __func__, params->cipher);
            return -EOPNOTSUPP;
    }
