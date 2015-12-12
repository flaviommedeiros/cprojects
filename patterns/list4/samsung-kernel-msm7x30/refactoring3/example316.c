switch ( pProfile->negotiatedUCEncryptionType )
    {
        case eCSR_ENCRYPT_TYPE_NONE:
        
            // for NO encryption, turn off Privacy and Rsn.
            PrivacyEnabled = 0;           
            RsnEnabled = 0;
            
            // WEP key length and Wep Default Key ID don't matter in this case....
            
            // clear out the WEP keys that may be hanging around.
            Key0Length = 0;
            Key1Length = 0;
            Key2Length = 0;
            Key3Length = 0;
            
            break;
            
        case eCSR_ENCRYPT_TYPE_WEP40_STATICKEY:
            
            // Privacy is ON.  NO RSN for Wep40 static key.
            PrivacyEnabled = 1;           
            RsnEnabled = 0;
                        
            // Set the Wep default key ID.
            WepDefaultKeyId = pProfile->Keys.defaultIndex;
            // Wep key size if 5 bytes (40 bits).
            WepKeyLength = WNI_CFG_WEP_KEY_LENGTH_5;            
            
            // set encryption keys in the CFG database or clear those that are not present in this profile.
            if ( pProfile->Keys.KeyLength[0] ) 
            {
                palCopyMemory( pMac->hHdd, Key0, pProfile->Keys.KeyMaterial[0], WNI_CFG_WEP_KEY_LENGTH_5 );
                Key0Length = WNI_CFG_WEP_KEY_LENGTH_5;
            }
            else
            {
                Key0Length = 0;
            }
            
            if ( pProfile->Keys.KeyLength[1] ) 
            {
                palCopyMemory( pMac->hHdd, Key1, pProfile->Keys.KeyMaterial[1], WNI_CFG_WEP_KEY_LENGTH_5 );
                Key1Length = WNI_CFG_WEP_KEY_LENGTH_5;
            }
            else
            {
                Key1Length = 0;
            }
            
            if ( pProfile->Keys.KeyLength[2] ) 
            {
                palCopyMemory( pMac->hHdd, Key2, pProfile->Keys.KeyMaterial[2], WNI_CFG_WEP_KEY_LENGTH_5 );
                Key2Length = WNI_CFG_WEP_KEY_LENGTH_5;                
            }
            else
            {
                Key2Length = 0;
            }
            
            if ( pProfile->Keys.KeyLength[3] ) 
            {
                palCopyMemory( pMac->hHdd, Key3, pProfile->Keys.KeyMaterial[3], WNI_CFG_WEP_KEY_LENGTH_5 );
                Key3Length = WNI_CFG_WEP_KEY_LENGTH_5;                
            }
            else
            {
                Key3Length = 0;
            }      
            break;
        
        case eCSR_ENCRYPT_TYPE_WEP104_STATICKEY:
            
            // Privacy is ON.  NO RSN for Wep40 static key.
            PrivacyEnabled = 1;           
            RsnEnabled = 0;
            
            // Set the Wep default key ID.
            WepDefaultKeyId = pProfile->Keys.defaultIndex;
           
            // Wep key size if 13 bytes (104 bits).
            WepKeyLength = WNI_CFG_WEP_KEY_LENGTH_13;
            
            // set encryption keys in the CFG database or clear those that are not present in this profile.
            if ( pProfile->Keys.KeyLength[0] ) 
            {
                palCopyMemory( pMac->hHdd, Key0, pProfile->Keys.KeyMaterial[ 0 ], WNI_CFG_WEP_KEY_LENGTH_13 );
                Key0Length = WNI_CFG_WEP_KEY_LENGTH_13;
            }
            else
            {
                Key0Length = 0;
            }
            
            if ( pProfile->Keys.KeyLength[1] ) 
            {
                palCopyMemory( pMac->hHdd, Key1, pProfile->Keys.KeyMaterial[ 1 ], WNI_CFG_WEP_KEY_LENGTH_13 );
                Key1Length = WNI_CFG_WEP_KEY_LENGTH_13;
            }
            else
            {
                Key1Length = 0;
            }
            
            if ( pProfile->Keys.KeyLength[2] ) 
            {
                palCopyMemory( pMac->hHdd, Key2, pProfile->Keys.KeyMaterial[ 2 ], WNI_CFG_WEP_KEY_LENGTH_13 );
                Key2Length = WNI_CFG_WEP_KEY_LENGTH_13;
            }
            else
            {
                Key2Length = 0;
            }
            
            if ( pProfile->Keys.KeyLength[3] ) 
            {
                palCopyMemory( pMac->hHdd, Key3, pProfile->Keys.KeyMaterial[ 3 ], WNI_CFG_WEP_KEY_LENGTH_13 );
                Key3Length = WNI_CFG_WEP_KEY_LENGTH_13;
            }
            else
            {
                Key3Length = 0;
            }
           
            break;
        
        case eCSR_ENCRYPT_TYPE_WEP40:
        case eCSR_ENCRYPT_TYPE_WEP104:
        case eCSR_ENCRYPT_TYPE_TKIP:
        case eCSR_ENCRYPT_TYPE_AES:
#ifdef FEATURE_WLAN_WAPI
        case eCSR_ENCRYPT_TYPE_WPI:
#endif /* FEATURE_WLAN_WAPI */
            // !! Note:  this is the only difference between this function and the csrSetCfgPrivacyFromProfile()
            // (setting of the privacy CFG based on the advertised privacy setting from the AP for WPA/WAPI associations ).        
            PrivacyEnabled = (0 != fPrivacy);
                         
            // turn on RSN enabled for WPA associations   
            RsnEnabled = 1;
            
            // WEP key length and Wep Default Key ID don't matter in this case....
            
            // clear out the static WEP keys that may be hanging around.
            Key0Length = 0;
            Key1Length = 0;
            Key2Length = 0;
            Key3Length = 0;        
          
            break;     
        default:
            PrivacyEnabled = 0;
            RsnEnabled = 0;
            break;            
    }
