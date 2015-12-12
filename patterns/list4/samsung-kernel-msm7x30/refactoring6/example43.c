if( (!HAL_STATUS_SUCCESS( status ) && ( NULL != pCommand )) 
#ifdef FEATURE_WLAN_CCX
            || ( eCSR_ENCRYPT_TYPE_KRK == pSetKey->encType ) 
#endif /* FEATURE_WLAN_CCX */
            )
    {
        csrReleaseCommandSetKey( pMac, pCommand );
    }
