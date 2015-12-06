switch (client->kind) {
        case CRM_CLIENT_IPC:
            return crm_ipcs_send(client, id, reply, FALSE);
#ifdef ENABLE_PCMK_REMOTE
        case CRM_CLIENT_TLS:
            return lrmd_tls_send_msg(client->remote, reply, id, "reply");
#endif
        default:
            crm_err("Unknown lrmd client type %d", client->kind);
    }
