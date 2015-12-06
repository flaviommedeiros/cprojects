const uint32_t OIDSupportedList[] PROGMEM = {
		/* Required General */
        OID_GEN_SUPPORTED_LIST            ,
        OID_GEN_HARDWARE_STATUS           ,
        OID_GEN_MEDIA_SUPPORTED           ,
        OID_GEN_MEDIA_IN_USE              ,
        OID_GEN_MAXIMUM_FRAME_SIZE        ,
        OID_GEN_LINK_SPEED                ,
        OID_GEN_TRANSMIT_BLOCK_SIZE       ,
        OID_GEN_RECEIVE_BLOCK_SIZE        ,
        OID_GEN_VENDOR_ID                 ,
        OID_GEN_VENDOR_DESCRIPTION        ,
        OID_GEN_CURRENT_PACKET_FILTER     ,
        OID_GEN_MAXIMUM_TOTAL_SIZE        ,
        OID_GEN_MEDIA_CONNECT_STATUS      ,
        OID_GEN_VENDOR_DRIVER_VERSION     ,
        OID_GEN_PHYSICAL_MEDIUM			  ,

		/* Required Statistical */
        OID_GEN_XMIT_OK                   ,
        OID_GEN_RCV_OK                    ,
        OID_GEN_XMIT_ERROR                ,
        OID_GEN_RCV_ERROR                 ,
        OID_GEN_RCV_NO_BUFFER             ,

		/* Please configure us        */
		OID_GEN_RNDIS_CONFIG_PARAMETER    ,


		/* IEEE 802.3 (Ethernet) OIDs */
        OID_802_3_PERMANENT_ADDRESS       ,
        OID_802_3_CURRENT_ADDRESS         ,
        OID_802_3_MULTICAST_LIST          ,
        OID_802_3_MAXIMUM_LIST_SIZE       ,
        OID_802_3_MAC_OPTIONS             ,
        OID_802_3_RCV_ERROR_ALIGNMENT     ,
        OID_802_3_XMIT_ONE_COLLISION      ,
        OID_802_3_XMIT_MORE_COLLISIONS    ,

/*802.11 OID's not fully implemented yet. Hence do not say we
  support them */
#if USB_ETH_EMULATE_WIFI
		/* 802.11 OIDs */
        OID_802_11_BSSID                  ,
        OID_802_11_SSID                   ,
        OID_802_11_NETWORK_TYPE_IN_USE    ,
        OID_802_11_RSSI                   ,
        OID_802_11_BSSID_LIST             ,
        OID_802_11_BSSID_LIST_SCAN        ,
        OID_802_11_INFRASTRUCTURE_MODE    ,
        OID_802_11_SUPPORTED_RATES        ,
        OID_802_11_CONFIGURATION          ,
        OID_802_11_ADD_WEP                ,
        OID_802_11_WEP_STATUS             ,
        OID_802_11_REMOVE_WEP             ,
        OID_802_11_DISASSOCIATE           ,
        OID_802_11_AUTHENTICATION_MODE    ,
        OID_802_11_RELOAD_DEFAULTS        ,
#endif

		/* Minimum power managment needed for USB */

		OID_PNP_CAPABILITIES              ,
		OID_PNP_QUERY_POWER               ,
		OID_PNP_SET_POWER                 ,

		OID_PNP_ENABLE_WAKE_UP            ,
		OID_PNP_ADD_WAKE_UP_PATTERN       ,
		OID_PNP_REMOVE_WAKE_UP_PATTERN
};
