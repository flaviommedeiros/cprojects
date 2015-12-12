if (( eSYSTEM_UNKNOWN_ROLE == systemRole ) || 
       (( eSYSTEM_STA_ROLE == systemRole )
#ifdef FEATURE_WLAN_CCX
      && frmType == HAL_TXRX_FRM_802_11_MGMT
#endif
            ))
   {
       txFlag |= HAL_USE_SELF_STA_REQUESTED_MASK;
   }
