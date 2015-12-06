switch (private->type) {
        case CRM_CLIENT_IPC:
            while (crm_ipc_ready(private->ipc)) {
                if (crm_ipc_read(private->ipc) > 0) {
                    const char *msg = crm_ipc_buffer(private->ipc);

                    lrmd_ipc_dispatch(msg, strlen(msg), lrmd);
                }
            }
            break;
#ifdef HAVE_GNUTLS_GNUTLS_H
        case CRM_CLIENT_TLS:
            lrmd_tls_dispatch(lrmd);
            break;
#endif
        default:
            crm_err("Unsupported connection type: %d", private->type);
    }
