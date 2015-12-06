switch (client->kind) {
            case CRM_CLIENT_IPC:
                if (crm_ipcs_sendv(client, update->iov, crm_ipc_server_event) < 0) {
                    crm_warn("Notification of client %s/%s failed", client->name, client->id);
                }
                break;
#ifdef HAVE_GNUTLS_GNUTLS_H
            case CRM_CLIENT_TLS:
#endif
            case CRM_CLIENT_TCP:
                crm_debug("Sent %s notification to client %s/%s", type, client->name, client->id);
                crm_remote_send(client->remote, update->msg);
                break;
            default:
                crm_err("Unknown transport %d for %s", client->kind, client->name);
        }
