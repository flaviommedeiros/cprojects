switch (native->type) {
        case CRM_CLIENT_IPC:
            return crm_ipc_ready(native->ipc);

#ifdef HAVE_GNUTLS_GNUTLS_H
        case CRM_CLIENT_TLS:
            if (native->pending_notify) {
                return 1;
            }

            return crm_remote_ready(native->remote, 0);
#endif
        default:
            crm_err("Unsupported connection type: %d", native->type);
    }
