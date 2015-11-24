switch (native->type) {
        case CRM_CLIENT_IPC:
            return crm_ipc_connected(native->ipc);
            break;
#ifdef HAVE_GNUTLS_GNUTLS_H
        case CRM_CLIENT_TLS:
            return lrmd_tls_connected(lrmd);
            break;
#endif
        default:
            crm_err("Unsupported connection type: %d", native->type);
    }
