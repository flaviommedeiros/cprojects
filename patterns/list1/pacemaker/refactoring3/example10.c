switch (native->type) {
        case CRM_CLIENT_IPC:
            /* fake async connection with ipc.  it should be fast
             * enough that we gain very little from async */
            rc = lrmd_api_connect(lrmd, name, NULL);
            if (!rc) {
                report_async_connection_result(lrmd, rc);
            }
            break;
#ifdef HAVE_GNUTLS_GNUTLS_H
        case CRM_CLIENT_TLS:
            rc = lrmd_tls_connect_async(lrmd, timeout);
            if (rc) {
                /* connection failed, report rc now */
                report_async_connection_result(lrmd, rc);
            }
            break;
#endif
        default:
            crm_err("Unsupported connection type: %d", native->type);
    }
