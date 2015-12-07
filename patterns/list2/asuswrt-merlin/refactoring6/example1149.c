if (ap_req.length
#ifndef NETSNMP_USE_KERBEROS_HEIMDAL
        && (ap_req.data[0] == 0x6e || ap_req.data[0] == 0x4e)) {
#else				/* NETSNMP_USE_KERBEROS_HEIMDAL */
        && (((char *)ap_req.data)[0] == 0x6e || ((char *)ap_req.data)[0] == 0x4e)) {
#endif

        /*
         * We need to initalize the authorization context, and set the
         * replay cache in it (and initialize the replay cache if we
         * haven't already
         */

        retcode = krb5_auth_con_init(kcontext, &auth_context);

        if (retcode) {
            DEBUGMSGTL(("ksm", "krb5_auth_con_init failed: %s\n",
                        error_message(retcode)));
            retval = SNMPERR_KRB5;
            snmp_set_detail(error_message(retcode));
            goto error;
        }

        if (!rcache) {
            krb5_data       server;
            server.data = "host";
            server.length = strlen(server.data);

            retcode = krb5_get_server_rcache(kcontext, &server, &rcache);

            if (retcode) {
                DEBUGMSGTL(("ksm", "krb5_get_server_rcache failed: %s\n",
                            error_message(retcode)));
                retval = SNMPERR_KRB5;
                snmp_set_detail(error_message(retcode));
                goto error;
            }
        }

        retcode = krb5_auth_con_setrcache(kcontext, auth_context, rcache);

        if (retcode) {
            DEBUGMSGTL(("ksm", "krb5_auth_con_setrcache failed: %s\n",
                        error_message(retcode)));
            retval = SNMPERR_KRB5;
            snmp_set_detail(error_message(retcode));
            goto error;
        }

        retcode = krb5_rd_req(kcontext, &auth_context, &ap_req, NULL,
                              keytab, &flags, &ticket);

        krb5_auth_con_setrcache(kcontext, auth_context, NULL);

        if (retcode) {
            DEBUGMSGTL(("ksm", "krb5_rd_req() failed: %s\n",
                        error_message(retcode)));
            retval = SNMPERR_KRB5;
            snmp_set_detail(error_message(retcode));
            goto error;
        }

        retcode =
            krb5_unparse_name(kcontext, TICKET_CLIENT(ticket), &cname);

        if (retcode == 0) {
            DEBUGMSGTL(("ksm", "KSM authenticated principal name: %s\n",
                        cname));
            free(cname);
        }

        /*
         * Check to make sure AP_OPTS_MUTUAL_REQUIRED was set
         */

        if (!(flags & AP_OPTS_MUTUAL_REQUIRED)) {
            DEBUGMSGTL(("ksm",
                        "KSM MUTUAL_REQUIRED not set in request!\n"));
            retval = SNMPERR_KRB5;
            snmp_set_detail("MUTUAL_REQUIRED not set in message");
            goto error;
        }

        retcode =
            krb5_auth_con_getremotesubkey(kcontext, auth_context, &subkey);

        if (retcode) {
            DEBUGMSGTL(("ksm", "KSM remote subkey retrieval failed: %s\n",
                        error_message(retcode)));
            retval = SNMPERR_KRB5;
            snmp_set_detail(error_message(retcode));
            goto error;
        }

#ifndef NETSNMP_USE_KERBEROS_HEIMDAL
    } else if (ap_req.length && (ap_req.data[0] == 0x6f ||
                                 ap_req.data[0] == 0x4f)) {
#else				/* NETSNMP_USE_KERBEROS_HEIMDAL */
    } else if (ap_req.length && (((char *)ap_req.data)[0] == 0x6f ||
                                 ((char *)ap_req.data)[0] == 0x4f)) {
#endif				/* NETSNMP_USE_KERBEROS_HEIMDAL */
        /*
         * Looks like a response; let's see if we've got that auth_context
         * in our cache.
         */

        krb5_ap_rep_enc_part *repl = NULL;

        response = 1;

        entry = ksm_get_cache(parms->pdu->msgid);

        if (!entry) {
            DEBUGMSGTL(("ksm",
                        "KSM: Unable to find auth_context for PDU with "
                        "message ID of %ld\n", parms->pdu->msgid));
            retval = SNMPERR_KRB5;
            goto error;
        }

        auth_context = entry->auth_context;

        /*
         * In that case, let's call the rd_rep function
         */

        retcode = krb5_rd_rep(kcontext, auth_context, &ap_req, &repl);

        if (repl)
            krb5_free_ap_rep_enc_part(kcontext, repl);

        if (retcode) {
            DEBUGMSGTL(("ksm", "KSM: krb5_rd_rep() failed: %s\n",
                        error_message(retcode)));
            retval = SNMPERR_KRB5;
            goto error;
        }

        DEBUGMSGTL(("ksm", "KSM: krb5_rd_rep() decoded successfully.\n"));

        retcode =
            krb5_auth_con_getlocalsubkey(kcontext, auth_context, &subkey);

        if (retcode) {
            DEBUGMSGTL(("ksm", "Unable to retrieve local subkey: %s\n",
                        error_message(retcode)));
            retval = SNMPERR_KRB5;
            snmp_set_detail("Unable to retrieve local subkey");
            goto error;
        }

    } else {
#ifndef NETSNMP_USE_KERBEROS_HEIMDAL
        DEBUGMSGTL(("ksm", "Unknown Kerberos message type (%02x)\n",
                    ap_req.data[0]));
#else 				/* NETSNMP_USE_KERBEROS_HEIMDAL */
	 DEBUGMSGTL(("ksm", "Unknown Kerberos message type (%02x)\n",
                    ((char *)ap_req.data)[0]));
#endif
        retval = SNMPERR_KRB5;
        snmp_set_detail("Unknown Kerberos message type");
        goto error;
    }
