switch (aSignal->SignalPrimitiveHeader.SignalId)
    {
        case CSR_MA_PACKET_REQUEST_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MA_PACKET_REQUEST);
        case CSR_MA_PACKET_CONFIRM_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MA_PACKET_CONFIRM);
        case CSR_MA_PACKET_INDICATION_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MA_PACKET_INDICATION);
        case CSR_MA_PACKET_CANCEL_REQUEST_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MA_PACKET_CANCEL_REQUEST);
        case CSR_MA_VIF_AVAILABILITY_RESPONSE_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MA_VIF_AVAILABILITY_RESPONSE);
        case CSR_MA_VIF_AVAILABILITY_INDICATION_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MA_VIF_AVAILABILITY_INDICATION);
        case CSR_MA_PACKET_ERROR_INDICATION_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MA_PACKET_ERROR_INDICATION);
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_RESET_REQUEST_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_RESET_REQUEST);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_RESET_CONFIRM_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_RESET_CONFIRM);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_GET_REQUEST_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_GET_REQUEST);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_GET_CONFIRM_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_GET_CONFIRM);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_SET_REQUEST_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_SET_REQUEST);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_SET_CONFIRM_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_SET_CONFIRM);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_GET_NEXT_REQUEST_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_GET_NEXT_REQUEST);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_GET_NEXT_CONFIRM_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_GET_NEXT_CONFIRM);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_POWERMGT_REQUEST_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_POWERMGT_REQUEST);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_POWERMGT_CONFIRM_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_POWERMGT_CONFIRM);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_SCAN_REQUEST_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_SCAN_REQUEST);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_SCAN_CONFIRM_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_SCAN_CONFIRM);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_HL_SYNC_REQUEST_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_HL_SYNC_REQUEST);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_HL_SYNC_CONFIRM_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_HL_SYNC_CONFIRM);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_MEASURE_REQUEST_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_MEASURE_REQUEST);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_MEASURE_CONFIRM_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_MEASURE_CONFIRM);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_MEASURE_INDICATION_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_MEASURE_INDICATION);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_SETKEYS_REQUEST_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_SETKEYS_REQUEST);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_SETKEYS_CONFIRM_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_SETKEYS_CONFIRM);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_DELETEKEYS_REQUEST_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_DELETEKEYS_REQUEST);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_DELETEKEYS_CONFIRM_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_DELETEKEYS_CONFIRM);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_AUTONOMOUS_SCAN_LOSS_INDICATION_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_AUTONOMOUS_SCAN_LOSS_INDICATION);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_CONNECTED_INDICATION_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_CONNECTED_INDICATION);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_SCAN_CANCEL_REQUEST_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_SCAN_CANCEL_REQUEST);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_HL_SYNC_CANCEL_REQUEST_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_HL_SYNC_CANCEL_REQUEST);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_HL_SYNC_CANCEL_CONFIRM_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_HL_SYNC_CANCEL_CONFIRM);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_ADD_PERIODIC_REQUEST_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_ADD_PERIODIC_REQUEST);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_ADD_PERIODIC_CONFIRM_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_ADD_PERIODIC_CONFIRM);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_DEL_PERIODIC_REQUEST_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_DEL_PERIODIC_REQUEST);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_DEL_PERIODIC_CONFIRM_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_DEL_PERIODIC_CONFIRM);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_ADD_AUTONOMOUS_SCAN_REQUEST_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_ADD_AUTONOMOUS_SCAN_REQUEST);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_ADD_AUTONOMOUS_SCAN_CONFIRM_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_ADD_AUTONOMOUS_SCAN_CONFIRM);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_DEL_AUTONOMOUS_SCAN_REQUEST_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_DEL_AUTONOMOUS_SCAN_REQUEST);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_DEL_AUTONOMOUS_SCAN_CONFIRM_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_DEL_AUTONOMOUS_SCAN_CONFIRM);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_SET_PACKET_FILTER_REQUEST_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_SET_PACKET_FILTER_REQUEST);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_SET_PACKET_FILTER_CONFIRM_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_SET_PACKET_FILTER_CONFIRM);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_STOP_MEASURE_REQUEST_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_STOP_MEASURE_REQUEST);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_STOP_MEASURE_CONFIRM_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_STOP_MEASURE_CONFIRM);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_PAUSE_AUTONOMOUS_SCAN_REQUEST_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_PAUSE_AUTONOMOUS_SCAN_REQUEST);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_PAUSE_AUTONOMOUS_SCAN_CONFIRM_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_PAUSE_AUTONOMOUS_SCAN_CONFIRM);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_AUTONOMOUS_SCAN_DONE_INDICATION_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_AUTONOMOUS_SCAN_DONE_INDICATION);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_ADD_TRIGGERED_GET_REQUEST_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_ADD_TRIGGERED_GET_REQUEST);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_ADD_TRIGGERED_GET_CONFIRM_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_ADD_TRIGGERED_GET_CONFIRM);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_DEL_TRIGGERED_GET_REQUEST_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_DEL_TRIGGERED_GET_REQUEST);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_DEL_TRIGGERED_GET_CONFIRM_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_DEL_TRIGGERED_GET_CONFIRM);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_TRIGGERED_GET_INDICATION_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_TRIGGERED_GET_INDICATION);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_ADD_BLACKOUT_REQUEST_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_ADD_BLACKOUT_REQUEST);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_ADD_BLACKOUT_CONFIRM_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_ADD_BLACKOUT_CONFIRM);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_BLACKOUT_ENDED_INDICATION_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_BLACKOUT_ENDED_INDICATION);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_DEL_BLACKOUT_REQUEST_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_DEL_BLACKOUT_REQUEST);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_DEL_BLACKOUT_CONFIRM_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_DEL_BLACKOUT_CONFIRM);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_ADD_RX_TRIGGER_REQUEST_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_ADD_RX_TRIGGER_REQUEST);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_ADD_RX_TRIGGER_CONFIRM_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_ADD_RX_TRIGGER_CONFIRM);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_DEL_RX_TRIGGER_REQUEST_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_DEL_RX_TRIGGER_REQUEST);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_DEL_RX_TRIGGER_CONFIRM_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_DEL_RX_TRIGGER_CONFIRM);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_CONNECT_STATUS_REQUEST_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_CONNECT_STATUS_REQUEST);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_CONNECT_STATUS_CONFIRM_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_CONNECT_STATUS_CONFIRM);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_MODIFY_BSS_PARAMETER_REQUEST_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_MODIFY_BSS_PARAMETER_REQUEST);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_MODIFY_BSS_PARAMETER_CONFIRM_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_MODIFY_BSS_PARAMETER_CONFIRM);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_ADD_TEMPLATE_REQUEST_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_ADD_TEMPLATE_REQUEST);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_ADD_TEMPLATE_CONFIRM_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_ADD_TEMPLATE_CONFIRM);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_CONFIG_QUEUE_REQUEST_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_CONFIG_QUEUE_REQUEST);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_CONFIG_QUEUE_CONFIRM_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_CONFIG_QUEUE_CONFIRM);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_ADD_TSPEC_REQUEST_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_ADD_TSPEC_REQUEST);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_ADD_TSPEC_CONFIRM_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_ADD_TSPEC_CONFIRM);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_DEL_TSPEC_REQUEST_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_DEL_TSPEC_REQUEST);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_DEL_TSPEC_CONFIRM_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_DEL_TSPEC_CONFIRM);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_START_AGGREGATION_REQUEST_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_START_AGGREGATION_REQUEST);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_START_AGGREGATION_CONFIRM_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_START_AGGREGATION_CONFIRM);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_BLOCKACK_ERROR_INDICATION_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_BLOCKACK_ERROR_INDICATION);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_STOP_AGGREGATION_REQUEST_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_STOP_AGGREGATION_REQUEST);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_STOP_AGGREGATION_CONFIRM_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_STOP_AGGREGATION_CONFIRM);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_SM_START_REQUEST_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_SM_START_REQUEST);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_SM_START_CONFIRM_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_SM_START_CONFIRM);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_LEAVE_REQUEST_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_LEAVE_REQUEST);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_LEAVE_CONFIRM_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_LEAVE_CONFIRM);
#endif
        case CSR_MLME_SET_TIM_REQUEST_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_SET_TIM_REQUEST);
        case CSR_MLME_SET_TIM_CONFIRM_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_SET_TIM_CONFIRM);
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_GET_KEY_SEQUENCE_REQUEST_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_GET_KEY_SEQUENCE_REQUEST);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_GET_KEY_SEQUENCE_CONFIRM_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_GET_KEY_SEQUENCE_CONFIRM);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_SET_CHANNEL_REQUEST_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_SET_CHANNEL_REQUEST);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_SET_CHANNEL_CONFIRM_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_SET_CHANNEL_CONFIRM);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_ADD_MULTICAST_ADDRESS_REQUEST_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_ADD_MULTICAST_ADDRESS_REQUEST);
#endif
#ifdef CSR_WIFI_HIP_FULL_SIGNAL_SET
        case CSR_MLME_ADD_MULTICAST_ADDRESS_CONFIRM_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_MLME_ADD_MULTICAST_ADDRESS_CONFIRM);
#endif
        case CSR_DEBUG_STRING_INDICATION_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_DEBUG_STRING_INDICATION);
        case CSR_DEBUG_WORD16_INDICATION_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_DEBUG_WORD16_INDICATION);
        case CSR_DEBUG_GENERIC_REQUEST_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_DEBUG_GENERIC_REQUEST);
        case CSR_DEBUG_GENERIC_CONFIRM_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_DEBUG_GENERIC_CONFIRM);
        case CSR_DEBUG_GENERIC_INDICATION_ID:
            return offsetof(struct CSR_SIGNAL_PRIMITIVE, u) + sizeof(CSR_DEBUG_GENERIC_INDICATION);
        default:
            return 0;
    }
