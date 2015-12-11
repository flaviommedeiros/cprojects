if ((s->session == NULL) || (s->session->ssl_version != s->version) ||
#ifdef OPENSSL_NO_TLSEXT
            !sess->session_id_length ||
#else
            (!sess->session_id_length && !sess->tlsext_tick) ||
#endif
            (s->session->not_resumable)) {
            if (!ssl_get_new_session(s, 0))
                goto err;
        }
