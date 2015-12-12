switch (id) {
        case CSR_MA_PACKET_ERROR_INDICATION_ID:
            process_ma_packet_error_ind(priv, &signal, &bulkdata);
            break;
        case CSR_MA_PACKET_INDICATION_ID:
            process_ma_packet_ind(priv, &signal, &bulkdata);
            break;
        case  CSR_MA_PACKET_CONFIRM_ID:
            process_ma_packet_cfm(priv, &signal, &bulkdata);
            break;
#ifdef CSR_SUPPORT_SME
        case CSR_MLME_SET_TIM_CONFIRM_ID:
            /* Handle TIM confirms from FW & set the station record's TIM state appropriately,
             * In case of failures, tries with max_retransmit limit
             */
            uf_handle_tim_cfm(priv, &signal.u.MlmeSetTimConfirm, signal.SignalPrimitiveHeader.ReceiverProcessId);
            break;
#endif
        case CSR_DEBUG_STRING_INDICATION_ID:
            debug_string_indication(priv, bulkdata.d[0].os_data_ptr, bulkdata.d[0].data_length);
            break;

        case CSR_DEBUG_WORD16_INDICATION_ID:
            debug_word16_indication(priv, &signal);
            break;

        case CSR_DEBUG_GENERIC_CONFIRM_ID:
        case CSR_DEBUG_GENERIC_INDICATION_ID:
            debug_generic_indication(priv, &signal);
            break;
        default:
            break;
    }
