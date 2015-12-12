if( (!CSR_IS_11n_ALLOWED( pProfile->negotiatedUCEncryptionType )) &&
                    ((eCSR_CFG_DOT11_MODE_11N == cfgDot11ModeToUse) ||
#ifdef WLAN_FEATURE_11AC
                     (eCSR_CFG_DOT11_MODE_11AC == cfgDot11ModeToUse) ||
#endif
                     (eCSR_CFG_DOT11_MODE_TAURUS == cfgDot11ModeToUse)) )
                {
                    //We cannot do 11n here
                    if( !CSR_IS_CHANNEL_5GHZ(pSirBssDesc->channelId) )
                    {
                        cfgDot11ModeToUse = eCSR_CFG_DOT11_MODE_11G;
                    }
                    else
                    {
                        cfgDot11ModeToUse = eCSR_CFG_DOT11_MODE_11A;
                    }
                }
