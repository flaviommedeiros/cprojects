switch (callback->type) {
        case evhtp_callback_type_hash:
            evhtp_safe_free(callback->val.path, free);
            break;
        case evhtp_callback_type_glob:
            evhtp_safe_free(callback->val.glob, free);
            break;
#ifndef EVHTP_DISABLE_REGEX
        case evhtp_callback_type_regex:
            regfree(callback->val.regex);
            evhtp_safe_free(callback->val.regex, free);
            break;
#endif
    }
