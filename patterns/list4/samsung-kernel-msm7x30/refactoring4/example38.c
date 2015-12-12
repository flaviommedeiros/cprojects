#ifdef WLAN_SOFTAP_FEATURE
if( ((!CSR_IS_INFRA_AP(pProfile )&& !CSR_IS_WDS(pProfile )) && 
         ((eCSR_CFG_DOT11_MODE_AUTO == pMac->roam.configParam.uCfgDot11Mode) ||
         (eCSR_CFG_DOT11_MODE_ABG == pMac->roam.configParam.uCfgDot11Mode))) ||
        (eCSR_CFG_DOT11_MODE_AUTO == cfgDot11Mode) || (eCSR_CFG_DOT11_MODE_ABG == cfgDot11Mode) )
#else
    if( (eCSR_CFG_DOT11_MODE_AUTO == pMac->roam.configParam.uCfgDot11Mode) ||
        (eCSR_CFG_DOT11_MODE_ABG == pMac->roam.configParam.uCfgDot11Mode) ||
        (eCSR_CFG_DOT11_MODE_AUTO == cfgDot11Mode) || (eCSR_CFG_DOT11_MODE_ABG == cfgDot11Mode) )
#endif
    {
        switch( pMac->roam.configParam.uCfgDot11Mode )
        {
            case eCSR_CFG_DOT11_MODE_11A:
                cfgDot11Mode = eCSR_CFG_DOT11_MODE_11A;
                eBand = eCSR_BAND_5G;
                break;
            case eCSR_CFG_DOT11_MODE_11B:
                cfgDot11Mode = eCSR_CFG_DOT11_MODE_11B;
                eBand = eCSR_BAND_24;
                break;
            case eCSR_CFG_DOT11_MODE_11G:
                cfgDot11Mode = eCSR_CFG_DOT11_MODE_11G;
                eBand = eCSR_BAND_24;
                break;            
            case eCSR_CFG_DOT11_MODE_11N:
                cfgDot11Mode = eCSR_CFG_DOT11_MODE_11N;
                eBand = eCSR_BAND_24;
                break;            
            //case eCSR_CFG_DOT11_MODE_BEST:
            //    cfgDot11Mode = eCSR_CFG_DOT11_MODE_BEST;
            //    eBand = eCSR_BAND_24;
            //    break;            
            default:
                // Global dot11 Mode setting is 11a/b/g.
                // use the channel number to determine the Mode setting.
                if ( eCSR_OPERATING_CHANNEL_AUTO == operationChn )
                {
                    eBand = pMac->roam.configParam.eBand;
                    if(eCSR_BAND_24 == eBand)
                    {
                        //See reason in else if ( CSR_IS_CHANNEL_24GHZ(operationChn) ) to pick 11B
                        cfgDot11Mode = eCSR_CFG_DOT11_MODE_11B;
                    }
                    else
                    {
                        //prefer 5GHz
                        eBand = eCSR_BAND_5G;
                        cfgDot11Mode = eCSR_CFG_DOT11_MODE_11A;
                    }
                }
                else if ( CSR_IS_CHANNEL_24GHZ(operationChn) )
                {
                    // channel is a 2.4GHz channel.  Set mode to 11g.
                    //
                    // !!LAC - WiFi tests require IBSS networks to start in 11b mode without any change to the
                    // default parameter settings on the adapter.  We use ACU to start an IBSS through creation
                    // of a startIBSS profile.   this startIBSS profile has Auto MACProtocol and the 
                    // adapter property setting for dot11Mode is also AUTO.   So in this case, let's start 
                    // the IBSS network in 11b mode instead of 11g mode.
                    //
                    // so this is for Auto=profile->MacProtocol && Auto=Global.dot11Mode && profile->channel is < 14, 
                    // then start the IBSS in b mode.
                    // 
                    // Note:  we used to have this start as an 11g IBSS for best performance... now to specify that
                    // the user will have to set the do11Mode in the property page to 11g to force it.
                    cfgDot11Mode = eCSR_CFG_DOT11_MODE_11B;
                    eBand = eCSR_BAND_24;
                }
                else 
                {   
                    // else, it's a 5.0GHz channel.  Set mode to 11a.
                    cfgDot11Mode = eCSR_CFG_DOT11_MODE_11A;
                    eBand = eCSR_BAND_5G;
                }
                break;
        }//switch
    }//if( eCSR_CFG_DOT11_MODE_ABG == cfgDot11Mode )
    else
    {
            //dot11 mode is set, lets pick the band
            if ( eCSR_OPERATING_CHANNEL_AUTO == operationChn )
            {
                // channel is Auto also. 
                eBand = pMac->roam.configParam.eBand;
                if(eCSR_BAND_ALL == eBand)
                {
                    //prefer 5GHz
                    eBand = eCSR_BAND_5G;
                }
            }
            else if ( CSR_IS_CHANNEL_24GHZ(operationChn) )
            {
                eBand = eCSR_BAND_24;
            }
            else 
            {   
                eBand = eCSR_BAND_5G;
            }
        }
