#if AP_SERVER_MAJORVERSION_NUMBER > 1 && AP_SERVER_MINORVERSION_NUMBER > 2
if ((msr == NULL)
        && ((info->level & APLOG_LEVELMASK) < APLOG_DEBUG)
        && apr_table_get(info->r->subprocess_env, "UNIQUE_ID"))
#else
    if ((msr == NULL)
        && ((level & APLOG_LEVELMASK) < APLOG_DEBUG)
        && apr_table_get(r->subprocess_env, "UNIQUE_ID"))
#endif
    {
#if AP_SERVER_MAJORVERSION_NUMBER > 1 && AP_SERVER_MINORVERSION_NUMBER > 2
        msr = create_tx_context((request_rec *)info->r);
#else
        msr = create_tx_context((request_rec *)r);
#endif
        if (msr != NULL && msr->txcfg->debuglog_level >= 9) {
            if (msr == NULL) {
                msr_log(msr, 9, "Failed to create context after request failure.");
            }
            else {
                msr_log(msr, 9, "Context created after request failure.");
            }
        }
    }
