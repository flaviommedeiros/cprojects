#ifdef WLAN_SOFTAP_FEATURE
if(pProfile && (CSR_IS_INFRA_AP(pProfile)) && (phyMode == eCSR_DOT11_MODE_11g_ONLY))
            cfgDot11Mode = eCSR_CFG_DOT11_MODE_11G_ONLY;
        else
#endif
        cfgDot11Mode = eCSR_CFG_DOT11_MODE_11G;
