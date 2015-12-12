static tBeaconFilterIe beaconFilterTable[] = {
   {SIR_MAC_DS_PARAM_SET_EID,    0, {0, 0, DS_PARAM_CHANNEL_MASK, 0}},
   {SIR_MAC_ERP_INFO_EID,        0, {0, 0, ERP_FILTER_MASK,       0}},
   {SIR_MAC_EDCA_PARAM_SET_EID,  0, {0, 0, EDCA_FILTER_MASK,      0}},
   {SIR_MAC_QOS_CAPABILITY_EID,  0, {0, 0, QOS_FILTER_MASK,       0}},
   {SIR_MAC_CHNL_SWITCH_ANN_EID, 1, {0, 0, 0,                     0}},
   {SIR_MAC_QUIET_EID,           1, {0, 0, 0,                     0}},
   {SIR_MAC_HT_INFO_EID,         0, {0, 0, HT_BYTE0_FILTER_MASK,  0}},  
   {SIR_MAC_HT_INFO_EID,         0, {2, 0, HT_BYTE2_FILTER_MASK,  0}}, 
   {SIR_MAC_HT_INFO_EID,         0, {5, 0, HT_BYTE5_FILTER_MASK,  0}}
#if defined WLAN_FEATURE_VOWIFI
   ,{SIR_MAC_PWR_CONSTRAINT_EID,  0, {0, 0, 0, 0}}
#endif
};
