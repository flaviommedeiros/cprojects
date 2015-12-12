switch( pTLCb->atlSTAClients[ucStaId].wSTADesc.wSTAType )
  {
      case WLAN_STA_IBSS:
        pw80211Header->wFrmCtrl.toDS          = 0;
        pw80211Header->wFrmCtrl.fromDS        = 0;
        /*Fix me*/
        vos_copy_macaddr( (v_MACADDR_t*)&pw80211Header->vA1,
              &pTLCb->atlSTAClients[ucStaId].wSTADesc.vSTAMACAddress);
        vos_mem_copy( pw80211Header->vA3,
              &pTLCb->atlSTAClients[ucStaId].wSTADesc.vBSSIDforIBSS ,
              VOS_MAC_ADDR_SIZE);
        break;

      case WLAN_STA_BT_AMP:
        *ucWDSEnabled = 1; // WDS on.
        pw80211Header->wFrmCtrl.toDS          = 1;
        pw80211Header->wFrmCtrl.fromDS        = 1;
        vos_copy_macaddr( (v_MACADDR_t*)&pw80211Header->vA1,
              &pTLCb->atlSTAClients[ucStaId].wSTADesc.vSTAMACAddress);
        vos_mem_copy( pw80211Header->vA2,
                w8023Header.vSA, VOS_MAC_ADDR_SIZE);
        vos_copy_macaddr( (v_MACADDR_t*)&pw80211Header->vA3,
              &pTLCb->atlSTAClients[ucStaId].wSTADesc.vSTAMACAddress);
        /* fill the optional A4 header */
        vos_mem_copy( pw80211Header->optvA4,
                w8023Header.vSA, VOS_MAC_ADDR_SIZE);
        TLLOG2(VOS_TRACE( VOS_MODULE_ID_TL, VOS_TRACE_LEVEL_INFO_HIGH,
            "BTAMP CASE NOW ---------staid=%d\n",
            ucStaId));
        break;

#ifdef WLAN_SOFTAP_FEATURE
      case WLAN_STA_SOFTAP:
        *ucWDSEnabled = 0; // WDS off.
        pw80211Header->wFrmCtrl.toDS          = 0;
        pw80211Header->wFrmCtrl.fromDS        = 1;
        /*Copy the DA to A1*/
        vos_mem_copy( pw80211Header->vA1, w8023Header.vDA , VOS_MAC_ADDR_SIZE);   
        vos_copy_macaddr( (v_MACADDR_t*)&pw80211Header->vA2,
              &pTLCb->atlSTAClients[ucStaId].wSTADesc.vSelfMACAddress);
        vos_mem_copy( pw80211Header->vA3,
                w8023Header.vSA, VOS_MAC_ADDR_SIZE);
        TLLOG2(VOS_TRACE( VOS_MODULE_ID_TL, VOS_TRACE_LEVEL_INFO_HIGH,
            "sw 802 to 80211 softap case  ---------staid=%d\n",
            ucStaId));
        break;
#endif

      case WLAN_STA_INFRA:
      default:
        pw80211Header->wFrmCtrl.toDS          = 1;
        pw80211Header->wFrmCtrl.fromDS        = 0;
        vos_copy_macaddr( (v_MACADDR_t*)&pw80211Header->vA1,
              &pTLCb->atlSTAClients[ucStaId].wSTADesc.vSTAMACAddress);
        vos_mem_copy( pw80211Header->vA3, w8023Header.vDA , VOS_MAC_ADDR_SIZE);
        TLLOG2(VOS_TRACE( VOS_MODULE_ID_TL, VOS_TRACE_LEVEL_INFO_HIGH,
            "REGULAR INFRA LINK CASE---------staid=%d\n",
            ucStaId));
        break;
  }
