switch (native->type) {
        case CRM_CLIENT_IPC:
            rc = lrmd_ipc_connect(lrmd, fd);
            break;
#ifdef HAVE_GNUTLS_GNUTLS_H
        case CRM_CLIENT_TLS:
            rc = lrmd_tls_connect(lrmd, fd);
            break;
#endif
        default:
            crm_err("Unsupported connection type: %d", native->type);
    }
