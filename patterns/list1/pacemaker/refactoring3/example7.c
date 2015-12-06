switch (native->type) {
        case CRM_CLIENT_IPC:
            rc = crm_ipc_send(native->ipc, msg, crm_ipc_flags_none, 0, NULL);
            break;
#ifdef HAVE_GNUTLS_GNUTLS_H
        case CRM_CLIENT_TLS:
            rc = lrmd_tls_send(lrmd, msg);
            if (rc == pcmk_ok) {
                /* we don't want to wait around for the reply, but
                 * since the request/reply protocol needs to behave the same
                 * as libqb, a reply will eventually come later anyway. */
                native->expected_late_replies++;
            }
            break;
#endif
        default:
            crm_err("Unsupported connection type: %d", native->type);
    }
