switch (client->kind) {
        case CRM_CLIENT_IPC:
            if (client->ipcs == NULL) {
                crm_trace("Asked to send event to disconnected local client");
                return -1;
            }
            return crm_ipcs_send(client, 0, msg, crm_ipc_server_event);
#ifdef ENABLE_PCMK_REMOTE
        case CRM_CLIENT_TLS:
            if (client->remote == NULL) {
                crm_trace("Asked to send event to disconnected remote client");
                return -1;
            }
            return lrmd_tls_send_msg(client->remote, msg, 0, "notify");
#endif
        default:
            crm_err("Unknown lrmd client type %d", client->kind);
    }
