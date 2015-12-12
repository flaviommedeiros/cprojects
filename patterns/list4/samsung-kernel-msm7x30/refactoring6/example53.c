if(
#ifdef FEATURE_WLAN_NON_INTEGRATED_SOC
      //For the new init sequence, CFGs need to apply before vos_start is call
      //No need to wait for ready state.
      SME_IS_READY(pMac) && 
#endif
      csrIsAllSessionDisconnected( pMac) )
   {
       csrSetGlobalCfgs(pMac);
   }
