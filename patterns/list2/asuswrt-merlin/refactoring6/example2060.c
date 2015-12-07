if (reqinfo->mode == MODE_GET ||
        reqinfo->mode == MODE_GETNEXT
#ifndef NETSNMP_NO_WRITE_SUPPORT
        || reqinfo->mode == MODE_SET_RESERVE1
#endif /* NETSNMP_NO_WRITE_SUPPORT */
        ) {
        /* per request last minute processing */
        for(request = requests ; request; request = request->next) {
            if (request->processed)
                continue;
            ti_info = (ti_cache_info*)
                netsnmp_request_get_list_data(request, TI_REQUEST_CACHE);
            table_info =
                netsnmp_extract_table_info(request);

            if (!ti_info)
                continue;
        
            switch(reqinfo->mode) {

            case MODE_GETNEXT:
                if (ti_info->best_match_len)
                    snmp_set_var_objid(request->requestvb, ti_info->best_match,
                                       ti_info->best_match_len);
                else {
                    coloid[reginfo->rootoid_len+1] = 
                        netsnmp_table_next_column(table_info);
                    if (0 == coloid[reginfo->rootoid_len+1]) {
                        /* out of range. */
                        coloid[reginfo->rootoid_len+1] = tbl_info->max_column + 1;
                        request->processed = TABLE_ITERATOR_NOTAGAIN;
                    }
                    snmp_set_var_objid(request->requestvb,
                                       coloid, reginfo->rootoid_len+2);
                    request->processed = 1;
                }
                snmp_free_varbind(table_info->indexes);
                table_info->indexes = snmp_clone_varbind(ti_info->results);
                /* FALL THROUGH */

            case MODE_GET:
#ifndef NETSNMP_NO_WRITE_SUPPORT
            case MODE_SET_RESERVE1:
#endif /* NETSNMP_NO_WRITE_SUPPORT */
                if (ti_info->data_context)
                    /* we don't add a free pointer, since it's in the
                       TI_REQUEST_CACHE instead */
                    netsnmp_request_add_list_data(request,
                                                  netsnmp_create_data_list
                                                  (TABLE_ITERATOR_NAME,
                                                   ti_info->data_context,
                                                   NULL));
                break;
            
            default:
                break;
            }
        }
            
        /* we change all GETNEXT operations into GET operations.
           why? because we're just so nice to the lower levels.
           maybe someday they'll pay us for it.  doubtful though. */
        oldmode = reqinfo->mode;
        if (reqinfo->mode == MODE_GETNEXT) {
            reqinfo->mode = MODE_GET;
        }
#ifndef NETSNMP_FEATURE_REMOVE_STASH_CACHE
    } else if (reqinfo->mode == MODE_GET_STASH) {
        netsnmp_free_request_data_sets(reqtmp);
        SNMP_FREE(reqtmp);
        table_info->indexes = old_indexes;
#endif  /* NETSNMP_FEATURE_REMOVE_STASH_CACHE */
    }
