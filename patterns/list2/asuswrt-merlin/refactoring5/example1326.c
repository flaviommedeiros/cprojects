#ifndef NETSNMP_DISABLE_SNMPV1
if (session.version == SNMP_VERSION_1) {
        if (inform) {
            fprintf(stderr, "Cannot send INFORM as SNMPv1 PDU\n");
            SOCK_CLEANUP;
            exit(1);
        }
        pdu = snmp_pdu_create(SNMP_MSG_TRAP);
        if ( !pdu ) {
            fprintf(stderr, "Failed to create trap PDU\n");
            SOCK_CLEANUP;
            exit(1);
        }
        pdu_in_addr_t = (in_addr_t *) pdu->agent_addr;
        if (arg == argc) {
            fprintf(stderr, "No enterprise oid\n");
            usage();
            SOCK_CLEANUP;
            exit(1);
        }
        if (argv[arg][0] == 0) {
            pdu->enterprise = (oid *) malloc(sizeof(objid_enterprise));
            memcpy(pdu->enterprise, objid_enterprise,
                   sizeof(objid_enterprise));
            pdu->enterprise_length =
                sizeof(objid_enterprise) / sizeof(oid);
        } else {
            name_length = MAX_OID_LEN;
            if (!snmp_parse_oid(argv[arg], name, &name_length)) {
                snmp_perror(argv[arg]);
                usage();
                SOCK_CLEANUP;
                exit(1);
            }
            pdu->enterprise = (oid *) malloc(name_length * sizeof(oid));
            memcpy(pdu->enterprise, name, name_length * sizeof(oid));
            pdu->enterprise_length = name_length;
        }
        if (++arg >= argc) {
            fprintf(stderr, "Missing agent parameter\n");
            usage();
            SOCK_CLEANUP;
            exit(1);
        }
        agent = argv[arg];
        if (agent != NULL && strlen(agent) != 0) {
            int ret = netsnmp_gethostbyname_v4(agent, pdu_in_addr_t);
            if (ret < 0) {
                fprintf(stderr, "unknown host: %s\n", agent);
                exit(1);
            }
        } else {
            *pdu_in_addr_t = get_myaddr();
        }
        if (++arg == argc) {
            fprintf(stderr, "Missing generic-trap parameter\n");
            usage();
            SOCK_CLEANUP;
            exit(1);
        }
        trap = argv[arg];
        pdu->trap_type = atoi(trap);
        if (++arg == argc) {
            fprintf(stderr, "Missing specific-trap parameter\n");
            usage();
            SOCK_CLEANUP;
            exit(1);
        }
        specific = argv[arg];
        pdu->specific_type = atoi(specific);
        if (++arg == argc) {
            fprintf(stderr, "Missing uptime parameter\n");
            usage();
            SOCK_CLEANUP;
            exit(1);
        }
        description = argv[arg];
        if (description == NULL || *description == 0)
            pdu->time = get_uptime();
        else
            pdu->time = atol(description);
    } else
#endif
    {
        long            sysuptime;
        char            csysuptime[20];

        pdu = snmp_pdu_create(inform ? SNMP_MSG_INFORM : SNMP_MSG_TRAP2);
        if ( !pdu ) {
            fprintf(stderr, "Failed to create notification PDU\n");
            SOCK_CLEANUP;
            exit(1);
        }
        if (arg == argc) {
            fprintf(stderr, "Missing up-time parameter\n");
            usage();
            SOCK_CLEANUP;
            exit(1);
        }
        trap = argv[arg];
        if (*trap == 0) {
            sysuptime = get_uptime();
            sprintf(csysuptime, "%ld", sysuptime);
            trap = csysuptime;
        }
        snmp_add_var(pdu, objid_sysuptime,
                     sizeof(objid_sysuptime) / sizeof(oid), 't', trap);
        if (++arg == argc) {
            fprintf(stderr, "Missing trap-oid parameter\n");
            usage();
            SOCK_CLEANUP;
            exit(1);
        }
        if (snmp_add_var
            (pdu, objid_snmptrap, sizeof(objid_snmptrap) / sizeof(oid),
             'o', argv[arg]) != 0) {
            snmp_perror(argv[arg]);
            SOCK_CLEANUP;
            exit(1);
        }
    }
