#ifdef WLAN_SOFTAP_FEATURE
if(pProfile && CSR_IS_INFRA_AP(pProfile))
           cfgDot11Mode = eCSR_CFG_DOT11_MODE_11N_ONLY;
       else
#endif
       cfgDot11Mode = eCSR_CFG_DOT11_MODE_11N;
