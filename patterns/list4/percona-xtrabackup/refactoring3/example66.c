switch (c->cmd) {
        case PROTOCOL_BINARY_CMD_VERSION:
            if (extlen == 0 && keylen == 0 && bodylen == 0) {
                write_bin_response(c, VERSION, 0, 0, strlen(VERSION));
            } else {
                protocol_error = 1;
            }
            break;
        case PROTOCOL_BINARY_CMD_FLUSH:
            if (keylen == 0 && bodylen == extlen && (extlen == 0 || extlen == 4)) {
                bin_read_key(c, bin_read_flush_exptime, extlen);
            } else {
                protocol_error = 1;
            }
            break;
        case PROTOCOL_BINARY_CMD_NOOP:
            if (extlen == 0 && keylen == 0 && bodylen == 0) {
                write_bin_response(c, NULL, 0, 0, 0);
            } else {
                protocol_error = 1;
            }
            break;
        case PROTOCOL_BINARY_CMD_SET: /* FALLTHROUGH */
        case PROTOCOL_BINARY_CMD_ADD: /* FALLTHROUGH */
        case PROTOCOL_BINARY_CMD_REPLACE:
            if (extlen == 8 && keylen != 0 && bodylen >= (keylen + 8)) {
                bin_read_key(c, bin_reading_set_header, 8);
            } else {
                protocol_error = 1;
            }
            break;
        case PROTOCOL_BINARY_CMD_GETQ:  /* FALLTHROUGH */
        case PROTOCOL_BINARY_CMD_GET:   /* FALLTHROUGH */
        case PROTOCOL_BINARY_CMD_GETKQ: /* FALLTHROUGH */
        case PROTOCOL_BINARY_CMD_GETK:
            if (extlen == 0 && bodylen == keylen && keylen > 0) {
                bin_read_key(c, bin_reading_get_key, 0);
            } else {
                protocol_error = 1;
            }
            break;
        case PROTOCOL_BINARY_CMD_DELETE:
            if (keylen > 0 && extlen == 0 && bodylen == keylen) {
                bin_read_key(c, bin_reading_del_header, extlen);
            } else {
                protocol_error = 1;
            }
            break;
        case PROTOCOL_BINARY_CMD_INCREMENT:
        case PROTOCOL_BINARY_CMD_DECREMENT:
            if (keylen > 0 && extlen == 20 && bodylen == (keylen + extlen)) {
                bin_read_key(c, bin_reading_incr_header, 20);
            } else {
                protocol_error = 1;
            }
            break;
        case PROTOCOL_BINARY_CMD_APPEND:
        case PROTOCOL_BINARY_CMD_PREPEND:
            if (keylen > 0 && extlen == 0) {
                bin_read_key(c, bin_reading_set_header, 0);
            } else {
                protocol_error = 1;
            }
            break;
        case PROTOCOL_BINARY_CMD_STAT:
            if (extlen == 0) {
                bin_read_key(c, bin_reading_stat, 0);
            } else {
                protocol_error = 1;
            }
            break;
        case PROTOCOL_BINARY_CMD_QUIT:
            if (keylen == 0 && extlen == 0 && bodylen == 0) {
                write_bin_response(c, NULL, 0, 0, 0);
                c->write_and_go = conn_closing;
                if (c->noreply) {
                    conn_set_state(c, conn_closing);
                }
            } else {
                protocol_error = 1;
            }
            break;
       case PROTOCOL_BINARY_CMD_TAP_CONNECT:
            if (settings.engine.v1->get_tap_iterator == NULL) {
                write_bin_packet(c, PROTOCOL_BINARY_RESPONSE_NOT_SUPPORTED, bodylen);
            } else {
                bin_read_chunk(c, bin_reading_packet,
                               c->binary_header.request.bodylen);
            }
            break;
       case PROTOCOL_BINARY_CMD_TAP_MUTATION:
       case PROTOCOL_BINARY_CMD_TAP_CHECKPOINT_START:
       case PROTOCOL_BINARY_CMD_TAP_CHECKPOINT_END:
       case PROTOCOL_BINARY_CMD_TAP_DELETE:
       case PROTOCOL_BINARY_CMD_TAP_FLUSH:
       case PROTOCOL_BINARY_CMD_TAP_OPAQUE:
       case PROTOCOL_BINARY_CMD_TAP_VBUCKET_SET:
            if (settings.engine.v1->tap_notify == NULL) {
                write_bin_packet(c, PROTOCOL_BINARY_RESPONSE_NOT_SUPPORTED, bodylen);
            } else {
                bin_read_chunk(c, bin_reading_packet, c->binary_header.request.bodylen);
            }
            break;
#ifdef SASL_ENABLED
        case PROTOCOL_BINARY_CMD_SASL_LIST_MECHS:
            if (extlen == 0 && keylen == 0 && bodylen == 0) {
                bin_list_sasl_mechs(c);
            } else {
                protocol_error = 1;
            }
            break;
        case PROTOCOL_BINARY_CMD_SASL_AUTH:
        case PROTOCOL_BINARY_CMD_SASL_STEP:
            if (extlen == 0 && keylen != 0) {
                bin_read_key(c, bin_reading_sasl_auth, 0);
            } else {
                protocol_error = 1;
            }
            break;
#endif
        case PROTOCOL_BINARY_CMD_VERBOSITY:
            if (extlen == 4 && keylen == 0 && bodylen == 4) {
                bin_read_chunk(c, bin_reading_packet,
                               c->binary_header.request.bodylen);
            } else {
                protocol_error = 1;
            }
            break;
        default:
            if (settings.engine.v1->unknown_command == NULL) {
                write_bin_packet(c, PROTOCOL_BINARY_RESPONSE_UNKNOWN_COMMAND,
                                bodylen);
            } else {
                bin_read_chunk(c, bin_reading_packet, c->binary_header.request.bodylen);
            }
    }
