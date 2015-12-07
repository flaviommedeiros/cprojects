if (command == SNMP_MSG_INFORM
        || command == SNMP_MSG_TRAP2
#ifndef NETSNMP_NO_WRITE_SUPPORT
        || command == SNMP_MSG_SET
#endif /* NETSNMP_NO_WRITE_SUPPORT */
        ) {
        printf("Type [i|u|s|x|d|n|o|t|a]: ");
        fflush(stdout);
        if (!fgets(buf, sizeof(buf), stdin)) {
            printf("Quitting,  Goodbye\n");
            SOCK_CLEANUP;
            exit(0);
        }
        ch = *buf;
        switch (ch) {
        case 'i':
            vp->type = ASN_INTEGER;
            break;
        case 'u':
            vp->type = ASN_UNSIGNED;
            break;
        case 's':
            vp->type = ASN_OCTET_STR;
            break;
        case 'x':
            vp->type = ASN_OCTET_STR;
            break;
        case 'd':
            vp->type = ASN_OCTET_STR;
            break;
        case 'n':
            vp->type = ASN_NULL;
            break;
        case 'o':
            vp->type = ASN_OBJECT_ID;
            break;
        case 't':
            vp->type = ASN_TIMETICKS;
            break;
        case 'a':
            vp->type = ASN_IPADDRESS;
            break;
        default:
            printf
                ("bad type \"%c\", use \"i\", \"u\", \"s\", \"x\", \"d\", \"n\", \"o\", \"t\", or \"a\".\n",
                 *buf);
            return -1;
        }
      getValue:
        printf("Value: ");
        fflush(stdout);
        if (!fgets(buf, sizeof(buf), stdin)) {
            printf("Quitting,  Goodbye\n");
            SOCK_CLEANUP;
            exit(0);
        }
        switch (vp->type) {
        case ASN_INTEGER:
            vp->val.integer = (long *) malloc(sizeof(long));
            *(vp->val.integer) = atoi(buf);
            vp->val_len = sizeof(long);
            break;
        case ASN_UNSIGNED:
            vp->val.integer = (long *) malloc(sizeof(long));
            *(vp->val.integer) = strtoul(buf, NULL, 0);
            vp->val_len = sizeof(long);
            break;
        case ASN_OCTET_STR:
            if (ch == 'd') {
                size_t          buf_len = 256;
                val_len = 0;
                if ((vp->val.string = (u_char *) malloc(buf_len)) == NULL) {
                    printf("malloc failure\n");
                    goto getValue;
                }
                if (!snmp_decimal_to_binary(&(vp->val.string), &buf_len,
                                            &val_len, 1, buf)) {
                    printf("Bad value or no sub-identifier > 255\n");
                    free(vp->val.string);
                    goto getValue;
                }
                vp->val_len = val_len;
            } else if (ch == 's') {
                /*
                 * -1 to omit trailing newline  
                 */
                vp->val.string = (u_char *) malloc(strlen(buf) - 1);
                if (vp->val.string == NULL) {
                    printf("malloc failure\n");
                    goto getValue;
                }
                memcpy(vp->val.string, buf, strlen(buf) - 1);
                vp->val.string[sizeof(vp->val.string)-1] = 0;
                vp->val_len = strlen(buf) - 1;
            } else if (ch == 'x') {
                size_t          buf_len = 256;
                val_len = 0;
                if ((vp->val.string = (u_char *) malloc(buf_len)) == NULL) {
                    printf("malloc failure\n");
                    goto getValue;
                }
                if (!snmp_hex_to_binary(&(vp->val.string), &buf_len,
                                        &val_len, 1, buf)) {
                    printf("Bad value (need pairs of hex digits)\n");
                    free(vp->val.string);
                    goto getValue;
                }
                vp->val_len = val_len;
            }
            break;
        case ASN_NULL:
            vp->val_len = 0;
            vp->val.string = NULL;
            break;
        case ASN_OBJECT_ID:
            if ('\n' == buf[strlen(buf) - 1])
                buf[strlen(buf) - 1] = '\0';
	    else {
		oid value[MAX_OID_LEN];
		vp->val_len = MAX_OID_LEN;
		if (0 == read_objid(buf, value, &vp->val_len)) {
		    printf("Unrecognised OID value\n");
		    goto getValue;
		}
		vp->val.objid = snmp_duplicate_objid(value, vp->val_len);
		vp->val_len *= sizeof(oid);
	    }
            break;
        case ASN_TIMETICKS:
            vp->val.integer = (long *) malloc(sizeof(long));
            *(vp->val.integer) = atoi(buf);
            vp->val_len = sizeof(long);
            break;
        case ASN_IPADDRESS:
            vp->val.integer = (long *) malloc(sizeof(long));
            *(vp->val.integer) = inet_addr(buf);
            vp->val_len = sizeof(long);
            break;
        default:
            printf("Internal error\n");
            break;
        }
    } else {                    /* some form of get message */
        vp->type = ASN_NULL;
        vp->val_len = 0;
    }
