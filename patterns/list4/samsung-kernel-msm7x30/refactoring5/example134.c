#ifdef FEATURE_WLAN_CCX
if (memcmp(auth_suite , ccpWpaOui06, 4) == 0) 
    {
        auth_type = eCSR_AUTH_TYPE_CCKM_WPA;
    } else 
#endif /* FEATURE_WLAN_CCX */
    { 
        auth_type = eCSR_AUTH_TYPE_UNKNOWN;
    }
