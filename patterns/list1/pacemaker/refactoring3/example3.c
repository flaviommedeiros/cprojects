switch (client_obj->kind) {
            case CRM_CLIENT_IPC:
                if (crm_ipcs_send(client_obj, rid, notify_src, sync_reply?crm_ipc_flags_none:crm_ipc_server_event) < 0) {
                    local_rc = -ENOMSG;
                }
                break;
#ifdef HAVE_GNUTLS_GNUTLS_H
            case CRM_CLIENT_TLS:
#endif
            case CRM_CLIENT_TCP:
                crm_remote_send(client_obj->remote, notify_src);
                break;
            default:
                crm_err("Unknown transport %d for %s", client_obj->kind, client_obj->name);
        }
