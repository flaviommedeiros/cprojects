#ifdef WLAN_SOFTAP_FEATURE
if(( pesessionEntry != NULL ) && (pesessionEntry->limSystemRole == eLIM_AP_ROLE )){
        if (pesessionEntry->gLimProtectionControl == WNI_CFG_FORCE_POLICY_PROTECTION_DISABLE )
            palZeroMemory( pMac->hHdd, (void *)&pesessionEntry->cfgProtection , sizeof(tCfgProtection));
        else{
            limLog(pMac, LOG1, FL(" frm11a = %d, from11b = %d, frm11g = %d, "
                                    "ht20 = %d, nongf = %d, lsigTxop = %d, "
                                    "rifs = %d, obss = %d\n"),    
                                    pesessionEntry->cfgProtection.fromlla,
                                    pesessionEntry->cfgProtection.fromllb,
                                    pesessionEntry->cfgProtection.fromllg,
                                    pesessionEntry->cfgProtection.ht20,
                                    pesessionEntry->cfgProtection.nonGf,
                                    pesessionEntry->cfgProtection.lsigTxop,
                                    pesessionEntry->cfgProtection.rifs,
                                    pesessionEntry->cfgProtection.obss);
        }
    }
    else{
#endif
    if (wlan_cfgGetInt(pMac, WNI_CFG_FORCE_POLICY_PROTECTION, &val) != eSIR_SUCCESS)
    {
        limLog(pMac, LOGP, FL("reading WNI_CFG_FORCE_POLICY_PROTECTION cfg failed\n"));
        return;
    }
    else
        pMac->lim.gLimProtectionControl = (tANI_U8)val;

    if (wlan_cfgGetInt(pMac, WNI_CFG_PROTECTION_ENABLED, &val) != eSIR_SUCCESS)
    {
        limLog(pMac, LOGP, FL("reading protection cfg failed\n"));
        return;
    }

    if(pMac->lim.gLimProtectionControl == WNI_CFG_FORCE_POLICY_PROTECTION_DISABLE)
        palZeroMemory( pMac->hHdd, (void *)&pMac->lim.cfgProtection , sizeof(tCfgProtection));
    else
        {
#if (defined(ANI_PRODUCT_TYPE_AP) || defined(ANI_PRODUCT_TYPE_AP_SDK))
            {
                pMac->lim.cfgProtection.overlapFromlla = (val >> WNI_CFG_PROTECTION_ENABLED_OLBC_FROM_llA) & 1;
                pMac->lim.cfgProtection.overlapFromllb = (val >> WNI_CFG_PROTECTION_ENABLED_OLBC_FROM_llB) & 1;
                pMac->lim.cfgProtection.overlapFromllg = (val >> WNI_CFG_PROTECTION_ENABLED_OLBC_FROM_llG) & 1;
                pMac->lim.cfgProtection.overlapHt20 = (val >> WNI_CFG_PROTECTION_ENABLED_OLBC_HT20) & 1;
                pMac->lim.cfgProtection.overlapNonGf = (val >> WNI_CFG_PROTECTION_ENABLED_OLBC_NON_GF) & 1;
                pMac->lim.cfgProtection.overlapLsigTxop = (val >> WNI_CFG_PROTECTION_ENABLED_OLBC_LSIG_TXOP) & 1;
                pMac->lim.cfgProtection.overlapRifs = (val >> WNI_CFG_PROTECTION_ENABLED_OLBC_RIFS) & 1;
                pMac->lim.cfgProtection.overlapOBSS = (val>> WNI_CFG_PROTECTION_ENABLED_OLBC_OBSS )&1;

            }
            #endif
            pMac->lim.cfgProtection.fromlla = (val >> WNI_CFG_PROTECTION_ENABLED_FROM_llA) & 1;
            pMac->lim.cfgProtection.fromllb = (val >> WNI_CFG_PROTECTION_ENABLED_FROM_llB) & 1;
            pMac->lim.cfgProtection.fromllg = (val >> WNI_CFG_PROTECTION_ENABLED_FROM_llG) & 1;
            pMac->lim.cfgProtection.ht20 = (val >> WNI_CFG_PROTECTION_ENABLED_HT_20) & 1;
            pMac->lim.cfgProtection.nonGf = (val >> WNI_CFG_PROTECTION_ENABLED_NON_GF) & 1;
            pMac->lim.cfgProtection.lsigTxop = (val >> WNI_CFG_PROTECTION_ENABLED_LSIG_TXOP) & 1;
            pMac->lim.cfgProtection.rifs = (val >> WNI_CFG_PROTECTION_ENABLED_RIFS) & 1;
            pMac->lim.cfgProtection.obss= (val >> WNI_CFG_PROTECTION_ENABLED_OBSS) & 1;

        }
#ifdef WLAN_SOFTAP_FEATURE
}
