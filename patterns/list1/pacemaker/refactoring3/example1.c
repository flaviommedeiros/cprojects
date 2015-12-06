switch (client->kind) {
        case CRM_CLIENT_TCP:
            csock = client->remote->tcp_socket;
            break;
#ifdef HAVE_GNUTLS_GNUTLS_H
        case CRM_CLIENT_TLS:
            if (client->remote->tls_session) {
                void *sock_ptr = gnutls_transport_get_ptr(*client->remote->tls_session);

                csock = GPOINTER_TO_INT(sock_ptr);
                if (client->remote->tls_handshake_complete) {
                    gnutls_bye(*client->remote->tls_session, GNUTLS_SHUT_WR);
                }
                gnutls_deinit(*client->remote->tls_session);
                gnutls_free(client->remote->tls_session);
                client->remote->tls_session = NULL;
            }
            break;
#endif
        default:
            crm_warn("Unexpected client type %d", client->kind);
    }
