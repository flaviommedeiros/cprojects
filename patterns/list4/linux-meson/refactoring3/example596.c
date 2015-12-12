switch (aSigID)
    {
        case CSR_MA_PACKET_REQUEST_ID:
            return 0x00000001;
        case CSR_MA_PACKET_CONFIRM_ID:
            return 0x00000002;
        case CSR_MA_PACKET_INDICATION_ID:
            return 0x00000004;
        case CSR_MA_PACKET_CANCEL_REQUEST_ID:
            return 0x00000008;
        case CSR_MA_VIF_AVAILABILITY_RESPONSE_ID:
            return 0x00000010;
        case CSR_MA_VIF_AVAILABILITY_INDICATION_ID:
            return 0x00000020;
        case CSR_MA_PACKET_ERROR_INDICATION_ID:
            return 0x00000040;
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_RESET_REQUEST_ID:
            return 0x00000080;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_RESET_CONFIRM_ID:
            return 0x00000100;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_GET_REQUEST_ID:
            return 0x00000200;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_GET_CONFIRM_ID:
            return 0x00000400;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_SET_REQUEST_ID:
            return 0x00000800;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_SET_CONFIRM_ID:
            return 0x00001000;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_GET_NEXT_REQUEST_ID:
            return 0x00002000;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_GET_NEXT_CONFIRM_ID:
            return 0x00004000;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_POWERMGT_REQUEST_ID:
            return 0x00008000;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_POWERMGT_CONFIRM_ID:
            return 0x00010001;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_SCAN_REQUEST_ID:
            return 0x00010002;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_SCAN_CONFIRM_ID:
            return 0x00010004;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_HL_SYNC_REQUEST_ID:
            return 0x00010008;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_HL_SYNC_CONFIRM_ID:
            return 0x00010010;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_MEASURE_REQUEST_ID:
            return 0x00010020;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_MEASURE_CONFIRM_ID:
            return 0x00010040;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_MEASURE_INDICATION_ID:
            return 0x00010080;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_SETKEYS_REQUEST_ID:
            return 0x00010100;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_SETKEYS_CONFIRM_ID:
            return 0x00010200;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_DELETEKEYS_REQUEST_ID:
            return 0x00010400;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_DELETEKEYS_CONFIRM_ID:
            return 0x00010800;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_AUTONOMOUS_SCAN_LOSS_INDICATION_ID:
            return 0x00011000;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_CONNECTED_INDICATION_ID:
            return 0x00012000;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_SCAN_CANCEL_REQUEST_ID:
            return 0x00014000;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_HL_SYNC_CANCEL_REQUEST_ID:
            return 0x00018000;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_HL_SYNC_CANCEL_CONFIRM_ID:
            return 0x00020001;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_ADD_PERIODIC_REQUEST_ID:
            return 0x00020002;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_ADD_PERIODIC_CONFIRM_ID:
            return 0x00020004;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_DEL_PERIODIC_REQUEST_ID:
            return 0x00020008;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_DEL_PERIODIC_CONFIRM_ID:
            return 0x00020010;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_ADD_AUTONOMOUS_SCAN_REQUEST_ID:
            return 0x00020020;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_ADD_AUTONOMOUS_SCAN_CONFIRM_ID:
            return 0x00020040;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_DEL_AUTONOMOUS_SCAN_REQUEST_ID:
            return 0x00020080;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_DEL_AUTONOMOUS_SCAN_CONFIRM_ID:
            return 0x00020100;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_SET_PACKET_FILTER_REQUEST_ID:
            return 0x00020200;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_SET_PACKET_FILTER_CONFIRM_ID:
            return 0x00020400;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_STOP_MEASURE_REQUEST_ID:
            return 0x00020800;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_STOP_MEASURE_CONFIRM_ID:
            return 0x00021000;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_PAUSE_AUTONOMOUS_SCAN_REQUEST_ID:
            return 0x00022000;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_PAUSE_AUTONOMOUS_SCAN_CONFIRM_ID:
            return 0x00024000;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_AUTONOMOUS_SCAN_DONE_INDICATION_ID:
            return 0x00028000;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_ADD_TRIGGERED_GET_REQUEST_ID:
            return 0x00030001;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_ADD_TRIGGERED_GET_CONFIRM_ID:
            return 0x00030002;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_DEL_TRIGGERED_GET_REQUEST_ID:
            return 0x00030004;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_DEL_TRIGGERED_GET_CONFIRM_ID:
            return 0x00030008;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_TRIGGERED_GET_INDICATION_ID:
            return 0x00030010;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_ADD_BLACKOUT_REQUEST_ID:
            return 0x00030020;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_ADD_BLACKOUT_CONFIRM_ID:
            return 0x00030040;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_BLACKOUT_ENDED_INDICATION_ID:
            return 0x00030080;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_DEL_BLACKOUT_REQUEST_ID:
            return 0x00030100;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_DEL_BLACKOUT_CONFIRM_ID:
            return 0x00030200;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_ADD_RX_TRIGGER_REQUEST_ID:
            return 0x00030400;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_ADD_RX_TRIGGER_CONFIRM_ID:
            return 0x00030800;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_DEL_RX_TRIGGER_REQUEST_ID:
            return 0x00031000;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_DEL_RX_TRIGGER_CONFIRM_ID:
            return 0x00032000;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_CONNECT_STATUS_REQUEST_ID:
            return 0x00034000;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_CONNECT_STATUS_CONFIRM_ID:
            return 0x00038000;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_MODIFY_BSS_PARAMETER_REQUEST_ID:
            return 0x00040001;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_MODIFY_BSS_PARAMETER_CONFIRM_ID:
            return 0x00040002;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_ADD_TEMPLATE_REQUEST_ID:
            return 0x00040004;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_ADD_TEMPLATE_CONFIRM_ID:
            return 0x00040008;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_CONFIG_QUEUE_REQUEST_ID:
            return 0x00040010;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_CONFIG_QUEUE_CONFIRM_ID:
            return 0x00040020;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_ADD_TSPEC_REQUEST_ID:
            return 0x00040040;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_ADD_TSPEC_CONFIRM_ID:
            return 0x00040080;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_DEL_TSPEC_REQUEST_ID:
            return 0x00040100;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_DEL_TSPEC_CONFIRM_ID:
            return 0x00040200;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_START_AGGREGATION_REQUEST_ID:
            return 0x00040400;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_START_AGGREGATION_CONFIRM_ID:
            return 0x00040800;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_BLOCKACK_ERROR_INDICATION_ID:
            return 0x00041000;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_STOP_AGGREGATION_REQUEST_ID:
            return 0x00042000;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_STOP_AGGREGATION_CONFIRM_ID:
            return 0x00044000;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_SM_START_REQUEST_ID:
            return 0x00048000;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_SM_START_CONFIRM_ID:
            return 0x00050001;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_LEAVE_REQUEST_ID:
            return 0x00050002;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_LEAVE_CONFIRM_ID:
            return 0x00050004;
#endif
        case CSR_MLME_SET_TIM_REQUEST_ID:
            return 0x00050008;
        case CSR_MLME_SET_TIM_CONFIRM_ID:
            return 0x00050010;
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_GET_KEY_SEQUENCE_REQUEST_ID:
            return 0x00050020;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_GET_KEY_SEQUENCE_CONFIRM_ID:
            return 0x00050040;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_SET_CHANNEL_REQUEST_ID:
            return 0x00050080;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_SET_CHANNEL_CONFIRM_ID:
            return 0x00050100;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_ADD_MULTICAST_ADDRESS_REQUEST_ID:
            return 0x00050200;
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_ADD_MULTICAST_ADDRESS_CONFIRM_ID:
            return 0x00050400;
#endif
        case CSR_DEBUG_STRING_INDICATION_ID:
            return 0x00050800;
        case CSR_DEBUG_WORD16_INDICATION_ID:
            return 0x00051000;
        case CSR_DEBUG_GENERIC_REQUEST_ID:
            return 0x00052000;
        case CSR_DEBUG_GENERIC_CONFIRM_ID:
            return 0x00054000;
        case CSR_DEBUG_GENERIC_INDICATION_ID:
            return 0x00058000;
        default:
            break;
    }
