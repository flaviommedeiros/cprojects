switch (type) {
        case evhtp_callback_type_hash:
            hcb->hash      = _evhtp_quick_hash(path);
            hcb->val.path  = strdup(path);
            break;
#ifndef EVHTP_DISABLE_REGEX
        case evhtp_callback_type_regex:
            hcb->val.regex = malloc(sizeof(regex_t));

            if (regcomp(hcb->val.regex, (char *)path, REG_EXTENDED) != 0) {
                evhtp_safe_free(hcb->val.regex, free);
                evhtp_safe_free(hcb, free);

                return NULL;
            }
            break;
#endif
        case evhtp_callback_type_glob:
            hcb->val.glob = strdup(path);
            break;
        default:
            evhtp_safe_free(hcb, free);

            return NULL;
    }
