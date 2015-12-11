switch(rx_payload[0])
    {
      case GZP_CMD_HOST_ADDRESS_REQ:
        gzp_process_address_req(rx_payload);
        break;

      #ifndef GZP_CRYPT_DISABLE

      case GZP_CMD_HOST_ID_REQ:
        gzp_process_id_req(rx_payload);
        break;
      case GZP_CMD_HOST_ID_FETCH:
        gzp_process_id_fetch(rx_payload);
        break;
      case GZP_CMD_KEY_UPDATE_PREPARE:
        gzp_process_key_update_prepare();
        break;
      case GZP_CMD_KEY_UPDATE:
        gzp_process_key_update(rx_payload);
        break;
      case GZP_CMD_ENCRYPTED_USER_DATA:
        gzp_process_encrypted_user_data(rx_payload, payload_length);
        break;

      #endif

      case GZP_CMD_FETCH_RESP:
      default:
        break;
    }
