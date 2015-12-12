#ifdef WLAN_FEATURE_VOWIFI_11R
if (memcmp(auth_suite , ccpRSNOui04, 4) == 0) 
    {
        // Check for 11r FT Authentication with PSK
        auth_type = eCSR_AUTH_TYPE_FT_RSN_PSK;
    } else 
    if (memcmp(auth_suite , ccpRSNOui03, 4) == 0) 
    {
        // Check for 11R FT Authentication with 802.1X
        auth_type = eCSR_AUTH_TYPE_FT_RSN;
    } else 
#endif
#ifdef FEATURE_WLAN_CCX
    if (memcmp(auth_suite , ccpRSNOui06, 4) == 0) 
    {
        auth_type = eCSR_AUTH_TYPE_CCKM_RSN;
    } else
#endif /* FEATURE_WLAN_CCX */
    { 
        auth_type = eCSR_AUTH_TYPE_UNKNOWN;
    }
