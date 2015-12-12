switch (callback->type) {
            case evhtp_callback_type_hash:
                if (strcmp(callback->val.path, path) == 0) {
                    *start_offset = 0;
                    *end_offset   = (unsigned int)strlen(path);

                    return callback;
                }
                break;
#ifndef EVHTP_DISABLE_REGEX
            case evhtp_callback_type_regex:
                if (regexec(callback->val.regex, path, callback->val.regex->re_nsub + 1, pmatch, 0) == 0) {
                    *start_offset = pmatch[callback->val.regex->re_nsub].rm_so;
                    *end_offset   = pmatch[callback->val.regex->re_nsub].rm_eo;

                    return callback;
                }

                break;
#endif
            case evhtp_callback_type_glob:
            {
                size_t path_len = strlen(path);
                size_t glob_len = strlen(callback->val.glob);

                if (_evhtp_glob_match(callback->val.glob, glob_len,
                                      path, path_len) == 1) {
                    *start_offset = 0;
                    *end_offset   = (unsigned int)path_len;

                    return callback;
                }
            }
            default:
                break;
        }
