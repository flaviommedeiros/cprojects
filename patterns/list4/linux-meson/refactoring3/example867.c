switch (signal_id)
    {
#ifdef UNIFI_SNIFF_ARPHRD
        case CSR_MA_SNIFFDATA_INDICATION_ID:
#endif
            break;

        case CSR_MA_PACKET_INDICATION_ID:
            if (!freeBulkData)
            {
                break;
            }
            /* FALLS THROUGH... */
        default:
            for (i = 0; i < UNIFI_MAX_DATA_REFERENCES; i++) {
                if (bulkdata->d[i].data_length != 0) {
                    unifi_net_data_free(priv, (void *)&bulkdata->d[i]);
                }
            }
    }
