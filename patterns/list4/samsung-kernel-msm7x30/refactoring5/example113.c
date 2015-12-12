#ifdef WLAN_FEATURE_VOWIFI_11R
if (csrRoamIs11rAssoc(pMac))
    {
        pftPreAuthReq->ft_ies_length = (tANI_U16)pMac->ft.ftSmeContext.auth_ft_ies_length;
        palCopyMemory(pMac->hHdd, pftPreAuthReq->ft_ies, pMac->ft.ftSmeContext.auth_ft_ies, 
                                pMac->ft.ftSmeContext.auth_ft_ies_length);
    }
    else
#endif
    {
        pftPreAuthReq->ft_ies_length = 0; 
    }
