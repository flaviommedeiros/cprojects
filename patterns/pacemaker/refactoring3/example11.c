switch (native->type) {
        case CRM_CLIENT_IPC:
            lrmd_ipc_disconnect(lrmd);
            break;
#ifdef HAVE_GNUTLS_GNUTLS_H
        case CRM_CLIENT_TLS:
            lrmd_tls_disconnect(lrmd);
            break;
#endif
        default:
            crm_err("Unsupported connection type: %d", native->type);
    }
