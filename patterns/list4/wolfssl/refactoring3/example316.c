switch (oid) {
            case BASIC_CA_OID:
                #ifdef OPENSSL_EXTRA
                    cert->extBasicConstSet = 1;
                    cert->extBasicConstCrit = critical;
                #endif
                if (DecodeBasicCaConstraint(&input[idx], length, cert) < 0)
                    return ASN_PARSE_E;
                break;

            case CRL_DIST_OID:
                if (DecodeCrlDist(&input[idx], length, cert) < 0)
                    return ASN_PARSE_E;
                break;

            case AUTH_INFO_OID:
                if (DecodeAuthInfo(&input[idx], length, cert) < 0)
                    return ASN_PARSE_E;
                break;

            case ALT_NAMES_OID:
                #ifdef OPENSSL_EXTRA
                    cert->extSubjAltNameSet = 1;
                    cert->extSubjAltNameCrit = critical;
                #endif
                if (DecodeAltNames(&input[idx], length, cert) < 0)
                    return ASN_PARSE_E;
                break;

            case AUTH_KEY_OID:
                cert->extAuthKeyIdSet = 1;
                #ifdef OPENSSL_EXTRA
                    cert->extAuthKeyIdCrit = critical;
                #endif
                if (DecodeAuthKeyId(&input[idx], length, cert) < 0)
                    return ASN_PARSE_E;
                break;

            case SUBJ_KEY_OID:
                cert->extSubjKeyIdSet = 1;
                #ifdef OPENSSL_EXTRA
                    cert->extSubjKeyIdCrit = critical;
                #endif
                if (DecodeSubjKeyId(&input[idx], length, cert) < 0)
                    return ASN_PARSE_E;
                break;

            case CERT_POLICY_OID:
                WOLFSSL_MSG("Certificate Policy extension not supported yet.");
                #ifdef WOLFSSL_SEP
                    #ifdef OPENSSL_EXTRA
                        cert->extCertPolicySet = 1;
                        cert->extCertPolicyCrit = critical;
                    #endif
                #endif
                #if defined(WOLFSSL_SEP) || defined(WOLFSSL_CERT_EXT)
                if (DecodeCertPolicy(&input[idx], length, cert) < 0)
                    return ASN_PARSE_E;
                #endif
                break;

            case KEY_USAGE_OID:
                cert->extKeyUsageSet = 1;
                #ifdef OPENSSL_EXTRA
                    cert->extKeyUsageCrit = critical;
                #endif
                if (DecodeKeyUsage(&input[idx], length, cert) < 0)
                    return ASN_PARSE_E;
                break;

            case EXT_KEY_USAGE_OID:
                cert->extExtKeyUsageSet = 1;
                #ifdef OPENSSL_EXTRA
                    cert->extExtKeyUsageCrit = critical;
                #endif
                if (DecodeExtKeyUsage(&input[idx], length, cert) < 0)
                    return ASN_PARSE_E;
                break;

            #ifndef IGNORE_NAME_CONSTRAINTS
            case NAME_CONS_OID:
                cert->extNameConstraintSet = 1;
                #ifdef OPENSSL_EXTRA
                    cert->extNameConstraintCrit = critical;
                #endif
                if (DecodeNameConstraints(&input[idx], length, cert) < 0)
                    return ASN_PARSE_E;
                break;
            #endif /* IGNORE_NAME_CONSTRAINTS */

            case INHIBIT_ANY_OID:
                WOLFSSL_MSG("Inhibit anyPolicy extension not supported yet.");
                break;

            default:
                /* While it is a failure to not support critical extensions,
                 * still parse the certificate ignoring the unsupported
                 * extention to allow caller to accept it with the verify
                 * callback. */
                if (critical)
                    criticalFail = 1;
                break;
        }
