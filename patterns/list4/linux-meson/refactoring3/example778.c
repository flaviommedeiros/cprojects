switch (sig->SignalPrimitiveHeader.SignalId)
    {
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_SET_PACKET_FILTER_CONFIRM_ID:
            sig->u.MlmeSetPacketFilterConfirm.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetPacketFilterConfirm.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetPacketFilterConfirm.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetPacketFilterConfirm.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetPacketFilterConfirm.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetPacketFilterConfirm.ResultCode = (CSR_RESULT_CODE) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_SETKEYS_CONFIRM_ID:
            sig->u.MlmeSetkeysConfirm.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetkeysConfirm.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetkeysConfirm.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetkeysConfirm.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetkeysConfirm.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetkeysConfirm.ResultCode = (CSR_RESULT_CODE) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_CONFIG_QUEUE_CONFIRM_ID:
            sig->u.MlmeConfigQueueConfirm.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeConfigQueueConfirm.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeConfigQueueConfirm.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeConfigQueueConfirm.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeConfigQueueConfirm.ResultCode = (CSR_RESULT_CODE) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_ADD_AUTONOMOUS_SCAN_CONFIRM_ID:
            sig->u.MlmeAddAutonomousScanConfirm.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddAutonomousScanConfirm.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddAutonomousScanConfirm.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddAutonomousScanConfirm.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddAutonomousScanConfirm.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddAutonomousScanConfirm.ResultCode = (CSR_RESULT_CODE) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddAutonomousScanConfirm.AutonomousScanId = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_ADD_BLACKOUT_CONFIRM_ID:
            sig->u.MlmeAddBlackoutConfirm.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddBlackoutConfirm.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddBlackoutConfirm.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddBlackoutConfirm.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddBlackoutConfirm.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddBlackoutConfirm.BlackoutId = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddBlackoutConfirm.ResultCode = (CSR_RESULT_CODE) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_DEL_BLACKOUT_REQUEST_ID:
            sig->u.MlmeDelBlackoutRequest.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelBlackoutRequest.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelBlackoutRequest.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelBlackoutRequest.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelBlackoutRequest.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelBlackoutRequest.BlackoutId = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_GET_KEY_SEQUENCE_CONFIRM_ID:
            sig->u.MlmeGetKeySequenceConfirm.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeGetKeySequenceConfirm.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeGetKeySequenceConfirm.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeGetKeySequenceConfirm.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeGetKeySequenceConfirm.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeGetKeySequenceConfirm.ResultCode = (CSR_RESULT_CODE) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeGetKeySequenceConfirm.SequenceNumber[0] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeGetKeySequenceConfirm.SequenceNumber[1] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeGetKeySequenceConfirm.SequenceNumber[2] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeGetKeySequenceConfirm.SequenceNumber[3] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeGetKeySequenceConfirm.SequenceNumber[4] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeGetKeySequenceConfirm.SequenceNumber[5] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeGetKeySequenceConfirm.SequenceNumber[6] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeGetKeySequenceConfirm.SequenceNumber[7] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_SM_START_CONFIRM_ID:
            sig->u.MlmeSmStartConfirm.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSmStartConfirm.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSmStartConfirm.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSmStartConfirm.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSmStartConfirm.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSmStartConfirm.ResultCode = (CSR_RESULT_CODE) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_STOP_AGGREGATION_CONFIRM_ID:
            sig->u.MlmeStopAggregationConfirm.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeStopAggregationConfirm.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeStopAggregationConfirm.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeStopAggregationConfirm.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeStopAggregationConfirm.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            memcpy(sig->u.MlmeStopAggregationConfirm.PeerQstaAddress.x, &ptr[index], 48 / 8);
            index += 48 / 8;
            sig->u.MlmeStopAggregationConfirm.UserPriority = (CSR_PRIORITY) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeStopAggregationConfirm.Direction = (CSR_DIRECTION) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeStopAggregationConfirm.ResultCode = (CSR_RESULT_CODE) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_DEL_TSPEC_REQUEST_ID:
            sig->u.MlmeDelTspecRequest.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelTspecRequest.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelTspecRequest.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelTspecRequest.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelTspecRequest.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelTspecRequest.UserPriority = (CSR_PRIORITY) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelTspecRequest.Direction = (CSR_DIRECTION) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
        case CSR_DEBUG_WORD16_INDICATION_ID:
            sig->u.DebugWord16Indication.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.DebugWord16Indication.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.DebugWord16Indication.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.DebugWord16Indication.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.DebugWord16Indication.DebugWords[0] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.DebugWord16Indication.DebugWords[1] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.DebugWord16Indication.DebugWords[2] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.DebugWord16Indication.DebugWords[3] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.DebugWord16Indication.DebugWords[4] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.DebugWord16Indication.DebugWords[5] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.DebugWord16Indication.DebugWords[6] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.DebugWord16Indication.DebugWords[7] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.DebugWord16Indication.DebugWords[8] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.DebugWord16Indication.DebugWords[9] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.DebugWord16Indication.DebugWords[10] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.DebugWord16Indication.DebugWords[11] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.DebugWord16Indication.DebugWords[12] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.DebugWord16Indication.DebugWords[13] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.DebugWord16Indication.DebugWords[14] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.DebugWord16Indication.DebugWords[15] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
        case CSR_DEBUG_GENERIC_CONFIRM_ID:
            sig->u.DebugGenericConfirm.DebugVariable.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.DebugGenericConfirm.DebugVariable.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.DebugGenericConfirm.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.DebugGenericConfirm.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.DebugGenericConfirm.DebugWords[0] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.DebugGenericConfirm.DebugWords[1] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.DebugGenericConfirm.DebugWords[2] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.DebugGenericConfirm.DebugWords[3] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.DebugGenericConfirm.DebugWords[4] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.DebugGenericConfirm.DebugWords[5] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.DebugGenericConfirm.DebugWords[6] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.DebugGenericConfirm.DebugWords[7] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
        case CSR_MA_PACKET_INDICATION_ID:
            sig->u.MaPacketIndication.Data.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MaPacketIndication.Data.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MaPacketIndication.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MaPacketIndication.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MaPacketIndication.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            memcpy(sig->u.MaPacketIndication.LocalTime.x, &ptr[index], 64 / 8);
            index += 64 / 8;
            sig->u.MaPacketIndication.Ifindex = (CSR_IFINTERFACE) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MaPacketIndication.Channel = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MaPacketIndication.ReceptionStatus = (CSR_RECEPTION_STATUS) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MaPacketIndication.Rssi = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MaPacketIndication.Snr = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MaPacketIndication.ReceivedRate = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
        case CSR_MLME_SET_TIM_REQUEST_ID:
            sig->u.MlmeSetTimRequest.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetTimRequest.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetTimRequest.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetTimRequest.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetTimRequest.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetTimRequest.AssociationId = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetTimRequest.TimValue = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_CONNECTED_INDICATION_ID:
            sig->u.MlmeConnectedIndication.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeConnectedIndication.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeConnectedIndication.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeConnectedIndication.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeConnectedIndication.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeConnectedIndication.ConnectionStatus = (CSR_CONNECTION_STATUS) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            memcpy(sig->u.MlmeConnectedIndication.PeerMacAddress.x, &ptr[index], 48 / 8);
            index += 48 / 8;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_DEL_RX_TRIGGER_REQUEST_ID:
            sig->u.MlmeDelRxTriggerRequest.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelRxTriggerRequest.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelRxTriggerRequest.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelRxTriggerRequest.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelRxTriggerRequest.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelRxTriggerRequest.TriggerId = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_TRIGGERED_GET_INDICATION_ID:
            sig->u.MlmeTriggeredGetIndication.MibAttributeValue.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeTriggeredGetIndication.MibAttributeValue.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeTriggeredGetIndication.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeTriggeredGetIndication.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeTriggeredGetIndication.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeTriggeredGetIndication.Status = (CSR_MIB_STATUS) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeTriggeredGetIndication.ErrorIndex = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeTriggeredGetIndication.TriggeredId = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_SCAN_REQUEST_ID:
            sig->u.MlmeScanRequest.ChannelList.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeScanRequest.ChannelList.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeScanRequest.InformationElements.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeScanRequest.InformationElements.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeScanRequest.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeScanRequest.Ifindex = (CSR_IFINTERFACE) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeScanRequest.ScanType = (CSR_SCAN_TYPE) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeScanRequest.ProbeDelay = CSR_GET_UINT32_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT32;
            sig->u.MlmeScanRequest.MinChannelTime = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeScanRequest.MaxChannelTime = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_DELETEKEYS_CONFIRM_ID:
            sig->u.MlmeDeletekeysConfirm.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDeletekeysConfirm.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDeletekeysConfirm.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDeletekeysConfirm.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDeletekeysConfirm.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDeletekeysConfirm.ResultCode = (CSR_RESULT_CODE) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_GET_NEXT_REQUEST_ID:
            sig->u.MlmeGetNextRequest.MibAttribute.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeGetNextRequest.MibAttribute.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeGetNextRequest.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeGetNextRequest.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_SET_CHANNEL_CONFIRM_ID:
            sig->u.MlmeSetChannelConfirm.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetChannelConfirm.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetChannelConfirm.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetChannelConfirm.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetChannelConfirm.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetChannelConfirm.ResultCode = (CSR_RESULT_CODE) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_START_AGGREGATION_REQUEST_ID:
            sig->u.MlmeStartAggregationRequest.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeStartAggregationRequest.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeStartAggregationRequest.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeStartAggregationRequest.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeStartAggregationRequest.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            memcpy(sig->u.MlmeStartAggregationRequest.PeerQstaAddress.x, &ptr[index], 48 / 8);
            index += 48 / 8;
            sig->u.MlmeStartAggregationRequest.UserPriority = (CSR_PRIORITY) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeStartAggregationRequest.Direction = (CSR_DIRECTION) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeStartAggregationRequest.StartingSequenceNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeStartAggregationRequest.BufferSize = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeStartAggregationRequest.BlockAckTimeout = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_HL_SYNC_REQUEST_ID:
            sig->u.MlmeHlSyncRequest.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeHlSyncRequest.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeHlSyncRequest.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeHlSyncRequest.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            memcpy(sig->u.MlmeHlSyncRequest.GroupAddress.x, &ptr[index], 48 / 8);
            index += 48 / 8;
            break;
#endif
        case CSR_DEBUG_GENERIC_REQUEST_ID:
            sig->u.DebugGenericRequest.DebugVariable.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.DebugGenericRequest.DebugVariable.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.DebugGenericRequest.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.DebugGenericRequest.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.DebugGenericRequest.DebugWords[0] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.DebugGenericRequest.DebugWords[1] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.DebugGenericRequest.DebugWords[2] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.DebugGenericRequest.DebugWords[3] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.DebugGenericRequest.DebugWords[4] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.DebugGenericRequest.DebugWords[5] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.DebugGenericRequest.DebugWords[6] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.DebugGenericRequest.DebugWords[7] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_LEAVE_CONFIRM_ID:
            sig->u.MlmeLeaveConfirm.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeLeaveConfirm.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeLeaveConfirm.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeLeaveConfirm.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeLeaveConfirm.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeLeaveConfirm.ResultCode = (CSR_RESULT_CODE) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_DEL_TRIGGERED_GET_REQUEST_ID:
            sig->u.MlmeDelTriggeredGetRequest.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelTriggeredGetRequest.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelTriggeredGetRequest.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelTriggeredGetRequest.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelTriggeredGetRequest.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelTriggeredGetRequest.TriggeredId = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_ADD_MULTICAST_ADDRESS_REQUEST_ID:
            sig->u.MlmeAddMulticastAddressRequest.Data.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddMulticastAddressRequest.Data.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddMulticastAddressRequest.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddMulticastAddressRequest.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddMulticastAddressRequest.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddMulticastAddressRequest.NumberOfMulticastGroupAddresses = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_RESET_REQUEST_ID:
            sig->u.MlmeResetRequest.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeResetRequest.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeResetRequest.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeResetRequest.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            memcpy(sig->u.MlmeResetRequest.StaAddress.x, &ptr[index], 48 / 8);
            index += 48 / 8;
            sig->u.MlmeResetRequest.SetDefaultMib = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_SCAN_CANCEL_REQUEST_ID:
            sig->u.MlmeScanCancelRequest.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeScanCancelRequest.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeScanCancelRequest.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeScanCancelRequest.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeScanCancelRequest.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_ADD_TRIGGERED_GET_CONFIRM_ID:
            sig->u.MlmeAddTriggeredGetConfirm.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddTriggeredGetConfirm.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddTriggeredGetConfirm.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddTriggeredGetConfirm.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddTriggeredGetConfirm.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddTriggeredGetConfirm.ResultCode = (CSR_RESULT_CODE) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddTriggeredGetConfirm.TriggeredId = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_SET_PACKET_FILTER_REQUEST_ID:
            sig->u.MlmeSetPacketFilterRequest.InformationElements.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetPacketFilterRequest.InformationElements.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetPacketFilterRequest.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetPacketFilterRequest.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetPacketFilterRequest.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetPacketFilterRequest.PacketFilterMode = (CSR_PACKET_FILTER_MODE) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetPacketFilterRequest.ArpFilterAddress = CSR_GET_UINT32_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT32;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_DEL_RX_TRIGGER_CONFIRM_ID:
            sig->u.MlmeDelRxTriggerConfirm.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelRxTriggerConfirm.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelRxTriggerConfirm.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelRxTriggerConfirm.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelRxTriggerConfirm.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelRxTriggerConfirm.TriggerId = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelRxTriggerConfirm.ResultCode = (CSR_RESULT_CODE) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_CONNECT_STATUS_REQUEST_ID:
            sig->u.MlmeConnectStatusRequest.InformationElements.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeConnectStatusRequest.InformationElements.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeConnectStatusRequest.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeConnectStatusRequest.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeConnectStatusRequest.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeConnectStatusRequest.ConnectionStatus = (CSR_CONNECTION_STATUS) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            memcpy(sig->u.MlmeConnectStatusRequest.StaAddress.x, &ptr[index], 48 / 8);
            index += 48 / 8;
            sig->u.MlmeConnectStatusRequest.AssociationId = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeConnectStatusRequest.AssociationCapabilityInformation = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_LEAVE_REQUEST_ID:
            sig->u.MlmeLeaveRequest.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeLeaveRequest.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeLeaveRequest.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeLeaveRequest.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeLeaveRequest.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_CONFIG_QUEUE_REQUEST_ID:
            sig->u.MlmeConfigQueueRequest.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeConfigQueueRequest.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeConfigQueueRequest.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeConfigQueueRequest.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeConfigQueueRequest.QueueIndex = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeConfigQueueRequest.Aifs = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeConfigQueueRequest.Cwmin = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeConfigQueueRequest.Cwmax = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeConfigQueueRequest.TxopLimit = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_DEL_TSPEC_CONFIRM_ID:
            sig->u.MlmeDelTspecConfirm.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelTspecConfirm.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelTspecConfirm.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelTspecConfirm.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelTspecConfirm.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelTspecConfirm.UserPriority = (CSR_PRIORITY) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelTspecConfirm.ResultCode = (CSR_RESULT_CODE) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
        case CSR_MLME_SET_TIM_CONFIRM_ID:
            sig->u.MlmeSetTimConfirm.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetTimConfirm.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetTimConfirm.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetTimConfirm.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetTimConfirm.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetTimConfirm.ResultCode = (CSR_RESULT_CODE) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_MEASURE_INDICATION_ID:
            sig->u.MlmeMeasureIndication.MeasurementReportSet.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeMeasureIndication.MeasurementReportSet.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeMeasureIndication.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeMeasureIndication.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeMeasureIndication.DialogToken = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_DEL_BLACKOUT_CONFIRM_ID:
            sig->u.MlmeDelBlackoutConfirm.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelBlackoutConfirm.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelBlackoutConfirm.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelBlackoutConfirm.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelBlackoutConfirm.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelBlackoutConfirm.BlackoutId = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelBlackoutConfirm.ResultCode = (CSR_RESULT_CODE) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_DEL_TRIGGERED_GET_CONFIRM_ID:
            sig->u.MlmeDelTriggeredGetConfirm.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelTriggeredGetConfirm.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelTriggeredGetConfirm.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelTriggeredGetConfirm.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelTriggeredGetConfirm.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelTriggeredGetConfirm.ResultCode = (CSR_RESULT_CODE) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelTriggeredGetConfirm.TriggeredId = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
        case CSR_DEBUG_GENERIC_INDICATION_ID:
            sig->u.DebugGenericIndication.DebugVariable.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.DebugGenericIndication.DebugVariable.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.DebugGenericIndication.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.DebugGenericIndication.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.DebugGenericIndication.DebugWords[0] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.DebugGenericIndication.DebugWords[1] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.DebugGenericIndication.DebugWords[2] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.DebugGenericIndication.DebugWords[3] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.DebugGenericIndication.DebugWords[4] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.DebugGenericIndication.DebugWords[5] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.DebugGenericIndication.DebugWords[6] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.DebugGenericIndication.DebugWords[7] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
        case CSR_MA_PACKET_CANCEL_REQUEST_ID:
            sig->u.MaPacketCancelRequest.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MaPacketCancelRequest.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MaPacketCancelRequest.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MaPacketCancelRequest.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MaPacketCancelRequest.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MaPacketCancelRequest.HostTag = CSR_GET_UINT32_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT32;
            break;
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_MODIFY_BSS_PARAMETER_CONFIRM_ID:
            sig->u.MlmeModifyBssParameterConfirm.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeModifyBssParameterConfirm.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeModifyBssParameterConfirm.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeModifyBssParameterConfirm.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeModifyBssParameterConfirm.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeModifyBssParameterConfirm.ResultCode = (CSR_RESULT_CODE) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_PAUSE_AUTONOMOUS_SCAN_CONFIRM_ID:
            sig->u.MlmePauseAutonomousScanConfirm.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmePauseAutonomousScanConfirm.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmePauseAutonomousScanConfirm.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmePauseAutonomousScanConfirm.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmePauseAutonomousScanConfirm.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmePauseAutonomousScanConfirm.ResultCode = (CSR_RESULT_CODE) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmePauseAutonomousScanConfirm.AutonomousScanId = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
        case CSR_MA_PACKET_REQUEST_ID:
            sig->u.MaPacketRequest.Data.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MaPacketRequest.Data.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MaPacketRequest.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MaPacketRequest.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MaPacketRequest.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MaPacketRequest.TransmitRate = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MaPacketRequest.HostTag = CSR_GET_UINT32_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT32;
            sig->u.MaPacketRequest.Priority = (CSR_PRIORITY) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            memcpy(sig->u.MaPacketRequest.Ra.x, &ptr[index], 48 / 8);
            index += 48 / 8;
            sig->u.MaPacketRequest.TransmissionControl = (CSR_TRANSMISSION_CONTROL) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_MODIFY_BSS_PARAMETER_REQUEST_ID:
            sig->u.MlmeModifyBssParameterRequest.Data.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeModifyBssParameterRequest.Data.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeModifyBssParameterRequest.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeModifyBssParameterRequest.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeModifyBssParameterRequest.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeModifyBssParameterRequest.BeaconPeriod = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeModifyBssParameterRequest.DtimPeriod = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeModifyBssParameterRequest.CapabilityInformation = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            memcpy(sig->u.MlmeModifyBssParameterRequest.Bssid.x, &ptr[index], 48 / 8);
            index += 48 / 8;
            sig->u.MlmeModifyBssParameterRequest.RtsThreshold = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_ADD_RX_TRIGGER_REQUEST_ID:
            sig->u.MlmeAddRxTriggerRequest.InformationElements.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddRxTriggerRequest.InformationElements.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddRxTriggerRequest.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddRxTriggerRequest.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddRxTriggerRequest.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddRxTriggerRequest.TriggerId = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddRxTriggerRequest.Priority = (CSR_PRIORITY) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
        case CSR_MA_VIF_AVAILABILITY_INDICATION_ID:
            sig->u.MaVifAvailabilityIndication.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MaVifAvailabilityIndication.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MaVifAvailabilityIndication.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MaVifAvailabilityIndication.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MaVifAvailabilityIndication.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MaVifAvailabilityIndication.Multicast = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_HL_SYNC_CANCEL_REQUEST_ID:
            sig->u.MlmeHlSyncCancelRequest.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeHlSyncCancelRequest.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeHlSyncCancelRequest.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeHlSyncCancelRequest.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            memcpy(sig->u.MlmeHlSyncCancelRequest.GroupAddress.x, &ptr[index], 48 / 8);
            index += 48 / 8;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_DEL_AUTONOMOUS_SCAN_REQUEST_ID:
            sig->u.MlmeDelAutonomousScanRequest.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelAutonomousScanRequest.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelAutonomousScanRequest.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelAutonomousScanRequest.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelAutonomousScanRequest.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelAutonomousScanRequest.AutonomousScanId = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_BLACKOUT_ENDED_INDICATION_ID:
            sig->u.MlmeBlackoutEndedIndication.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeBlackoutEndedIndication.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeBlackoutEndedIndication.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeBlackoutEndedIndication.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeBlackoutEndedIndication.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeBlackoutEndedIndication.BlackoutId = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_AUTONOMOUS_SCAN_DONE_INDICATION_ID:
            sig->u.MlmeAutonomousScanDoneIndication.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAutonomousScanDoneIndication.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAutonomousScanDoneIndication.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAutonomousScanDoneIndication.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAutonomousScanDoneIndication.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAutonomousScanDoneIndication.ResultCode = (CSR_RESULT_CODE) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAutonomousScanDoneIndication.AutonomousScanId = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_GET_KEY_SEQUENCE_REQUEST_ID:
            sig->u.MlmeGetKeySequenceRequest.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeGetKeySequenceRequest.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeGetKeySequenceRequest.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeGetKeySequenceRequest.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeGetKeySequenceRequest.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeGetKeySequenceRequest.KeyId = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeGetKeySequenceRequest.KeyType = (CSR_KEY_TYPE) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            memcpy(sig->u.MlmeGetKeySequenceRequest.Address.x, &ptr[index], 48 / 8);
            index += 48 / 8;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_SET_CHANNEL_REQUEST_ID:
            sig->u.MlmeSetChannelRequest.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetChannelRequest.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetChannelRequest.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetChannelRequest.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetChannelRequest.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetChannelRequest.Ifindex = (CSR_IFINTERFACE) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetChannelRequest.Channel = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            memcpy(sig->u.MlmeSetChannelRequest.Address.x, &ptr[index], 48 / 8);
            index += 48 / 8;
            sig->u.MlmeSetChannelRequest.AvailabilityDuration = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetChannelRequest.AvailabilityInterval = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_MEASURE_CONFIRM_ID:
            sig->u.MlmeMeasureConfirm.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeMeasureConfirm.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeMeasureConfirm.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeMeasureConfirm.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeMeasureConfirm.ResultCode = (CSR_RESULT_CODE) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeMeasureConfirm.DialogToken = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_ADD_TRIGGERED_GET_REQUEST_ID:
            sig->u.MlmeAddTriggeredGetRequest.MibAttribute.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddTriggeredGetRequest.MibAttribute.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddTriggeredGetRequest.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddTriggeredGetRequest.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddTriggeredGetRequest.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddTriggeredGetRequest.TriggeredId = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_AUTONOMOUS_SCAN_LOSS_INDICATION_ID:
            sig->u.MlmeAutonomousScanLossIndication.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAutonomousScanLossIndication.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAutonomousScanLossIndication.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAutonomousScanLossIndication.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAutonomousScanLossIndication.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            memcpy(sig->u.MlmeAutonomousScanLossIndication.Bssid.x, &ptr[index], 48 / 8);
            index += 48 / 8;
            break;
#endif
        case CSR_MA_VIF_AVAILABILITY_RESPONSE_ID:
            sig->u.MaVifAvailabilityResponse.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MaVifAvailabilityResponse.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MaVifAvailabilityResponse.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MaVifAvailabilityResponse.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MaVifAvailabilityResponse.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MaVifAvailabilityResponse.ResultCode = (CSR_RESULT_CODE) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_ADD_TEMPLATE_REQUEST_ID:
            sig->u.MlmeAddTemplateRequest.Data1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddTemplateRequest.Data1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddTemplateRequest.Data2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddTemplateRequest.Data2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddTemplateRequest.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddTemplateRequest.FrameType = (CSR_FRAME_TYPE) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddTemplateRequest.MinTransmitRate = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_POWERMGT_CONFIRM_ID:
            sig->u.MlmePowermgtConfirm.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmePowermgtConfirm.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmePowermgtConfirm.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmePowermgtConfirm.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmePowermgtConfirm.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmePowermgtConfirm.ResultCode = (CSR_RESULT_CODE) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_ADD_PERIODIC_CONFIRM_ID:
            sig->u.MlmeAddPeriodicConfirm.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddPeriodicConfirm.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddPeriodicConfirm.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddPeriodicConfirm.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddPeriodicConfirm.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddPeriodicConfirm.PeriodicId = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddPeriodicConfirm.ResultCode = (CSR_RESULT_CODE) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_GET_CONFIRM_ID:
            sig->u.MlmeGetConfirm.MibAttributeValue.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeGetConfirm.MibAttributeValue.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeGetConfirm.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeGetConfirm.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeGetConfirm.Status = (CSR_MIB_STATUS) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeGetConfirm.ErrorIndex = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_GET_NEXT_CONFIRM_ID:
            sig->u.MlmeGetNextConfirm.MibAttributeValue.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeGetNextConfirm.MibAttributeValue.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeGetNextConfirm.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeGetNextConfirm.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeGetNextConfirm.Status = (CSR_MIB_STATUS) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeGetNextConfirm.ErrorIndex = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_STOP_AGGREGATION_REQUEST_ID:
            sig->u.MlmeStopAggregationRequest.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeStopAggregationRequest.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeStopAggregationRequest.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeStopAggregationRequest.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeStopAggregationRequest.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            memcpy(sig->u.MlmeStopAggregationRequest.PeerQstaAddress.x, &ptr[index], 48 / 8);
            index += 48 / 8;
            sig->u.MlmeStopAggregationRequest.UserPriority = (CSR_PRIORITY) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeStopAggregationRequest.Direction = (CSR_DIRECTION) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_ADD_RX_TRIGGER_CONFIRM_ID:
            sig->u.MlmeAddRxTriggerConfirm.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddRxTriggerConfirm.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddRxTriggerConfirm.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddRxTriggerConfirm.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddRxTriggerConfirm.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddRxTriggerConfirm.TriggerId = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddRxTriggerConfirm.ResultCode = (CSR_RESULT_CODE) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_ADD_BLACKOUT_REQUEST_ID:
            sig->u.MlmeAddBlackoutRequest.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddBlackoutRequest.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddBlackoutRequest.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddBlackoutRequest.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddBlackoutRequest.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddBlackoutRequest.BlackoutId = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddBlackoutRequest.BlackoutType = (CSR_BLACKOUT_TYPE) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddBlackoutRequest.BlackoutSource = (CSR_BLACKOUT_SOURCE) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddBlackoutRequest.BlackoutStartReference = CSR_GET_UINT32_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT32;
            sig->u.MlmeAddBlackoutRequest.BlackoutPeriod = CSR_GET_UINT32_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT32;
            sig->u.MlmeAddBlackoutRequest.BlackoutDuration = CSR_GET_UINT32_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT32;
            memcpy(sig->u.MlmeAddBlackoutRequest.PeerStaAddress.x, &ptr[index], 48 / 8);
            index += 48 / 8;
            sig->u.MlmeAddBlackoutRequest.BlackoutCount = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_DELETEKEYS_REQUEST_ID:
            sig->u.MlmeDeletekeysRequest.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDeletekeysRequest.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDeletekeysRequest.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDeletekeysRequest.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDeletekeysRequest.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDeletekeysRequest.KeyId = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDeletekeysRequest.KeyType = (CSR_KEY_TYPE) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            memcpy(sig->u.MlmeDeletekeysRequest.Address.x, &ptr[index], 48 / 8);
            index += 48 / 8;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_RESET_CONFIRM_ID:
            sig->u.MlmeResetConfirm.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeResetConfirm.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeResetConfirm.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeResetConfirm.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeResetConfirm.ResultCode = (CSR_RESULT_CODE) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_HL_SYNC_CONFIRM_ID:
            sig->u.MlmeHlSyncConfirm.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeHlSyncConfirm.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeHlSyncConfirm.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeHlSyncConfirm.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            memcpy(sig->u.MlmeHlSyncConfirm.GroupAddress.x, &ptr[index], 48 / 8);
            index += 48 / 8;
            sig->u.MlmeHlSyncConfirm.ResultCode = (CSR_RESULT_CODE) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_ADD_AUTONOMOUS_SCAN_REQUEST_ID:
            sig->u.MlmeAddAutonomousScanRequest.ChannelList.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddAutonomousScanRequest.ChannelList.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddAutonomousScanRequest.InformationElements.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddAutonomousScanRequest.InformationElements.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddAutonomousScanRequest.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddAutonomousScanRequest.AutonomousScanId = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddAutonomousScanRequest.Ifindex = (CSR_IFINTERFACE) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddAutonomousScanRequest.ChannelStartingFactor = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddAutonomousScanRequest.ScanType = (CSR_SCAN_TYPE) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddAutonomousScanRequest.ProbeDelay = CSR_GET_UINT32_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT32;
            sig->u.MlmeAddAutonomousScanRequest.MinChannelTime = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddAutonomousScanRequest.MaxChannelTime = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_SET_REQUEST_ID:
            sig->u.MlmeSetRequest.MibAttributeValue.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetRequest.MibAttributeValue.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetRequest.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetRequest.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_SM_START_REQUEST_ID:
            sig->u.MlmeSmStartRequest.Beacon.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSmStartRequest.Beacon.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSmStartRequest.BssParameters.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSmStartRequest.BssParameters.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSmStartRequest.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSmStartRequest.Ifindex = (CSR_IFINTERFACE) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSmStartRequest.Channel = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            memcpy(sig->u.MlmeSmStartRequest.InterfaceAddress.x, &ptr[index], 48 / 8);
            index += 48 / 8;
            memcpy(sig->u.MlmeSmStartRequest.Bssid.x, &ptr[index], 48 / 8);
            index += 48 / 8;
            sig->u.MlmeSmStartRequest.BeaconPeriod = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSmStartRequest.DtimPeriod = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSmStartRequest.CapabilityInformation = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_CONNECT_STATUS_CONFIRM_ID:
            sig->u.MlmeConnectStatusConfirm.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeConnectStatusConfirm.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeConnectStatusConfirm.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeConnectStatusConfirm.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeConnectStatusConfirm.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeConnectStatusConfirm.ResultCode = (CSR_RESULT_CODE) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_DEL_AUTONOMOUS_SCAN_CONFIRM_ID:
            sig->u.MlmeDelAutonomousScanConfirm.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelAutonomousScanConfirm.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelAutonomousScanConfirm.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelAutonomousScanConfirm.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelAutonomousScanConfirm.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelAutonomousScanConfirm.ResultCode = (CSR_RESULT_CODE) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelAutonomousScanConfirm.AutonomousScanId = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_DEL_PERIODIC_REQUEST_ID:
            sig->u.MlmeDelPeriodicRequest.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelPeriodicRequest.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelPeriodicRequest.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelPeriodicRequest.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelPeriodicRequest.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelPeriodicRequest.PeriodicId = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_SETKEYS_REQUEST_ID:
            sig->u.MlmeSetkeysRequest.Key.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetkeysRequest.Key.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetkeysRequest.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetkeysRequest.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetkeysRequest.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetkeysRequest.Length = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetkeysRequest.KeyId = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetkeysRequest.KeyType = (CSR_KEY_TYPE) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            memcpy(sig->u.MlmeSetkeysRequest.Address.x, &ptr[index], 48 / 8);
            index += 48 / 8;
            sig->u.MlmeSetkeysRequest.SequenceNumber[0] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetkeysRequest.SequenceNumber[1] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetkeysRequest.SequenceNumber[2] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetkeysRequest.SequenceNumber[3] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetkeysRequest.SequenceNumber[4] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetkeysRequest.SequenceNumber[5] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetkeysRequest.SequenceNumber[6] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetkeysRequest.SequenceNumber[7] = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            memcpy(&sig->u.MlmeSetkeysRequest.CipherSuiteSelector, &ptr[index], 32 / 8);
            index += 32 / 8;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_PAUSE_AUTONOMOUS_SCAN_REQUEST_ID:
            sig->u.MlmePauseAutonomousScanRequest.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmePauseAutonomousScanRequest.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmePauseAutonomousScanRequest.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmePauseAutonomousScanRequest.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmePauseAutonomousScanRequest.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmePauseAutonomousScanRequest.AutonomousScanId = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmePauseAutonomousScanRequest.Pause = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_GET_REQUEST_ID:
            sig->u.MlmeGetRequest.MibAttribute.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeGetRequest.MibAttribute.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeGetRequest.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeGetRequest.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_POWERMGT_REQUEST_ID:
            sig->u.MlmePowermgtRequest.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmePowermgtRequest.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmePowermgtRequest.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmePowermgtRequest.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmePowermgtRequest.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmePowermgtRequest.PowerManagementMode = (CSR_POWER_MANAGEMENT_MODE) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmePowermgtRequest.ReceiveDtims = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmePowermgtRequest.ListenInterval = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmePowermgtRequest.TrafficWindow = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
        case CSR_MA_PACKET_ERROR_INDICATION_ID:
            sig->u.MaPacketErrorIndication.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MaPacketErrorIndication.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MaPacketErrorIndication.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MaPacketErrorIndication.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MaPacketErrorIndication.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            memcpy(sig->u.MaPacketErrorIndication.PeerQstaAddress.x, &ptr[index], 48 / 8);
            index += 48 / 8;
            sig->u.MaPacketErrorIndication.UserPriority = (CSR_PRIORITY) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MaPacketErrorIndication.SequenceNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_ADD_PERIODIC_REQUEST_ID:
            sig->u.MlmeAddPeriodicRequest.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddPeriodicRequest.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddPeriodicRequest.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddPeriodicRequest.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddPeriodicRequest.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddPeriodicRequest.PeriodicId = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddPeriodicRequest.MaximumLatency = CSR_GET_UINT32_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT32;
            sig->u.MlmeAddPeriodicRequest.PeriodicSchedulingMode = (CSR_PERIODIC_SCHEDULING_MODE) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddPeriodicRequest.WakeHost = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddPeriodicRequest.UserPriority = (CSR_PRIORITY) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_ADD_TSPEC_REQUEST_ID:
            sig->u.MlmeAddTspecRequest.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddTspecRequest.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddTspecRequest.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddTspecRequest.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddTspecRequest.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddTspecRequest.UserPriority = (CSR_PRIORITY) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddTspecRequest.Direction = (CSR_DIRECTION) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddTspecRequest.PsScheme = (CSR_PS_SCHEME) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddTspecRequest.MediumTime = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddTspecRequest.ServiceStartTime = CSR_GET_UINT32_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT32;
            sig->u.MlmeAddTspecRequest.ServiceInterval = CSR_GET_UINT32_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT32;
            sig->u.MlmeAddTspecRequest.MinimumDataRate = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_ADD_MULTICAST_ADDRESS_CONFIRM_ID:
            sig->u.MlmeAddMulticastAddressConfirm.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddMulticastAddressConfirm.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddMulticastAddressConfirm.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddMulticastAddressConfirm.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddMulticastAddressConfirm.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddMulticastAddressConfirm.ResultCode = (CSR_RESULT_CODE) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_ADD_TSPEC_CONFIRM_ID:
            sig->u.MlmeAddTspecConfirm.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddTspecConfirm.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddTspecConfirm.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddTspecConfirm.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddTspecConfirm.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddTspecConfirm.UserPriority = (CSR_PRIORITY) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddTspecConfirm.ResultCode = (CSR_RESULT_CODE) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_HL_SYNC_CANCEL_CONFIRM_ID:
            sig->u.MlmeHlSyncCancelConfirm.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeHlSyncCancelConfirm.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeHlSyncCancelConfirm.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeHlSyncCancelConfirm.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeHlSyncCancelConfirm.ResultCode = (CSR_RESULT_CODE) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_SCAN_CONFIRM_ID:
            sig->u.MlmeScanConfirm.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeScanConfirm.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeScanConfirm.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeScanConfirm.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeScanConfirm.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeScanConfirm.ResultCode = (CSR_RESULT_CODE) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
        case CSR_DEBUG_STRING_INDICATION_ID:
            sig->u.DebugStringIndication.DebugMessage.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.DebugStringIndication.DebugMessage.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.DebugStringIndication.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.DebugStringIndication.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_ADD_TEMPLATE_CONFIRM_ID:
            sig->u.MlmeAddTemplateConfirm.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddTemplateConfirm.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddTemplateConfirm.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddTemplateConfirm.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddTemplateConfirm.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddTemplateConfirm.FrameType = (CSR_FRAME_TYPE) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeAddTemplateConfirm.ResultCode = (CSR_RESULT_CODE) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_BLOCKACK_ERROR_INDICATION_ID:
            sig->u.MlmeBlockackErrorIndication.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeBlockackErrorIndication.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeBlockackErrorIndication.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeBlockackErrorIndication.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeBlockackErrorIndication.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeBlockackErrorIndication.ResultCode = (CSR_REASON_CODE) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            memcpy(sig->u.MlmeBlockackErrorIndication.PeerQstaAddress.x, &ptr[index], 48 / 8);
            index += 48 / 8;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_SET_CONFIRM_ID:
            sig->u.MlmeSetConfirm.MibAttributeValue.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetConfirm.MibAttributeValue.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetConfirm.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetConfirm.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetConfirm.Status = (CSR_MIB_STATUS) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeSetConfirm.ErrorIndex = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_MEASURE_REQUEST_ID:
            sig->u.MlmeMeasureRequest.MeasurementRequestSet.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeMeasureRequest.MeasurementRequestSet.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeMeasureRequest.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeMeasureRequest.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeMeasureRequest.DialogToken = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_START_AGGREGATION_CONFIRM_ID:
            sig->u.MlmeStartAggregationConfirm.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeStartAggregationConfirm.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeStartAggregationConfirm.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeStartAggregationConfirm.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeStartAggregationConfirm.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            memcpy(sig->u.MlmeStartAggregationConfirm.PeerQstaAddress.x, &ptr[index], 48 / 8);
            index += 48 / 8;
            sig->u.MlmeStartAggregationConfirm.UserPriority = (CSR_PRIORITY) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeStartAggregationConfirm.Direction = (CSR_DIRECTION) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeStartAggregationConfirm.ResultCode = (CSR_RESULT_CODE) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeStartAggregationConfirm.SequenceNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_STOP_MEASURE_CONFIRM_ID:
            sig->u.MlmeStopMeasureConfirm.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeStopMeasureConfirm.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeStopMeasureConfirm.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeStopMeasureConfirm.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeStopMeasureConfirm.ResultCode = (CSR_RESULT_CODE) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeStopMeasureConfirm.DialogToken = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
        case CSR_MA_PACKET_CONFIRM_ID:
            sig->u.MaPacketConfirm.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MaPacketConfirm.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MaPacketConfirm.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MaPacketConfirm.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MaPacketConfirm.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MaPacketConfirm.TransmissionStatus = (CSR_TRANSMISSION_STATUS) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MaPacketConfirm.RetryCount = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MaPacketConfirm.Rate = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MaPacketConfirm.HostTag = CSR_GET_UINT32_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT32;
            break;
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_DEL_PERIODIC_CONFIRM_ID:
            sig->u.MlmeDelPeriodicConfirm.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelPeriodicConfirm.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelPeriodicConfirm.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelPeriodicConfirm.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelPeriodicConfirm.VirtualInterfaceIdentifier = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelPeriodicConfirm.PeriodicId = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeDelPeriodicConfirm.ResultCode = (CSR_RESULT_CODE) CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_STOP_MEASURE_REQUEST_ID:
            sig->u.MlmeStopMeasureRequest.Dummydataref1.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeStopMeasureRequest.Dummydataref1.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeStopMeasureRequest.Dummydataref2.SlotNumber = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeStopMeasureRequest.Dummydataref2.DataLength = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            sig->u.MlmeStopMeasureRequest.DialogToken = CSR_GET_UINT16_FROM_LITTLE_ENDIAN(ptr + index);
            index += SIZEOF_UINT16;
            break;
#endif

        default:
            return CSR_WIFI_HIP_RESULT_INVALID_VALUE;
    }
