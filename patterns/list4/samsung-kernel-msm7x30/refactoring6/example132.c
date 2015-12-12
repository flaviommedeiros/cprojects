if ( (psessionEntry->limSmeState == eLIM_SME_WT_DISASSOC_STATE) || 
         (psessionEntry->limSmeState == eLIM_SME_WT_DEAUTH_STATE)
#ifdef WLAN_SOFTAP_FEATURE
          || (psessionEntry->limSystemRole == eLIM_AP_ROLE )   
#endif
     )
    {       
        pStaDs = dphLookupHashEntry(pMac, smeDisassocCnf.peerMacAddr, &aid, &psessionEntry->dph.dphHashTable);
        if (pStaDs == NULL)
        {
            PELOGW(limLog(pMac, LOGW, FL("received DISASSOC_CNF for a STA that does not have context, addr= "));
            limPrintMacAddr(pMac, smeDisassocCnf.peerMacAddr, LOGW);)
            return;
        }
        /* Delete FT session if there exists one */
        limFTCleanup(pMac);
        limCleanupRxPath(pMac, pStaDs, psessionEntry);
    }
