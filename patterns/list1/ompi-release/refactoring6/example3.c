if (NULL == mca_oob_tcp_component.ipv4conns
#if OPAL_ENABLE_IPV6
        && NULL == mca_oob_tcp_component.ipv6conns
#endif
        ) {
        ORTE_ERROR_LOG(ORTE_ERR_NOT_FOUND);
        return ORTE_ERR_NOT_FOUND;
    }
