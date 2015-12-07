if (reqinfo->mode == MODE_GET ||
        reqinfo->mode == MODE_GETNEXT ||
        reqinfo->mode == MODE_GET_STASH
#ifndef NETSNMP_NO_WRITE_SUPPORT
        || reqinfo->mode == MODE_SET_RESERVE1
#endif /* NETSNMP_NO_WRITE_SUPPORT */
        ) {
        /*
         * Count the number of request in the list,
         *   so that we'll know when we're finished
         */
        for(request = requests ; request; request = request->next)
          if (!request->processed)
            request_count++;
        notdone = 1;
        hintok = 1;
        while(notdone) {
            notdone = 0;

            /* find first data point */
            if (!index_search) {
                if (free_this_index_search) {
                    /* previously done */
                    index_search = free_this_index_search;
                } else {
                    for(request=requests ; request; request=request->next) {
                        table_info = netsnmp_extract_table_info(request);
                        if (table_info)
                            break;
                    }
                    if (!table_info) {
                        snmp_log(LOG_WARNING,
                                 "no valid requests for iterator table %s\n",
                                 reginfo->handlerName);
                        netsnmp_free_request_data_sets(reqtmp);
                        SNMP_FREE(reqtmp);
                        return SNMP_ERR_NOERROR;
                    }
                    index_search = snmp_clone_varbind(table_info->indexes);
                    free_this_index_search = index_search;

                    /* setup, malloc search data: */
                    if (!index_search) {
                        /*
                         * hmmm....  invalid table? 
                         */
                        snmp_log(LOG_WARNING,
                                 "invalid index list or failed malloc for table %s\n",
                                 reginfo->handlerName);
                        netsnmp_free_request_data_sets(reqtmp);
                        SNMP_FREE(reqtmp);
                        return SNMP_ERR_NOERROR;
                    }
                }
            }

            /* if sorted, pass in a hint */
            if (hintok && (iinfo->flags & NETSNMP_ITERATOR_FLAG_SORTED)) {
                callback_loop_context = table_info;
            }
            index_search =
                (iinfo->get_first_data_point) (&callback_loop_context,
                                               &callback_data_context,
                                               index_search, iinfo);

            /* loop over each data point */
            while(index_search) {

                /* remember to free this later */
                free_this_index_search = index_search;
            
                /* compare against each request*/
                for(request = requests ; request; request = request->next) {
                    if (request->processed)
                        continue;

                    /* XXX: store in an array for faster retrieval */
                    table_info = netsnmp_extract_table_info(request);
                    if (table_info == NULL) {
                        /*
                         * Cleanup 
                         */
                        if (free_this_index_search)
                            snmp_free_varbind(free_this_index_search);
                        netsnmp_free_request_data_sets(reqtmp);
                        SNMP_FREE(reqtmp);
                        return SNMP_ERR_GENERR;
                    }
                    coloid[reginfo->rootoid_len + 1] = table_info->colnum;

                    ti_info = (ti_cache_info*)
                        netsnmp_request_get_list_data(request, TI_REQUEST_CACHE);

                    switch(reqinfo->mode) {
                    case MODE_GET:
#ifndef NETSNMP_NO_WRITE_SUPPORT
                    case MODE_SET_RESERVE1:
#endif /* NETSNMP_NO_WRITE_SUPPORT */
                        /* looking for exact matches */
                        build_oid_noalloc(myname, MAX_OID_LEN, &myname_len,
                                          coloid, coloid_len, index_search);
                        if (snmp_oid_compare(myname, myname_len,
                                             request->requestvb->name,
                                             request->requestvb->name_length) == 0) {
                            /* 
                             * keep this
                             */
                            if (netsnmp_iterator_remember(request,
                                                          myname,
                                                          myname_len,
                                                          callback_data_context,
                                                          callback_loop_context,
                                                          iinfo) == NULL) {
                                /*
                                 * Cleanup 
                                 */
                                if (free_this_index_search)
                                    snmp_free_varbind
                                        (free_this_index_search);
                                netsnmp_free_request_data_sets(reqtmp);
                                SNMP_FREE(reqtmp);
                                return SNMP_ERR_GENERR;
                            }
                            request_count--;   /* One less to look for */
                        } else {
                            if (iinfo->free_data_context && callback_data_context) {
                                (iinfo->free_data_context)(callback_data_context,
                                                           iinfo);
                            }
                        }
                        break;

#ifndef NETSNMP_FEATURE_REMOVE_STASH_CACHE
                    case MODE_GET_STASH:
                        /* collect data for each column for every row */
                        build_oid_noalloc(myname, MAX_OID_LEN, &myname_len,
                                          coloid, coloid_len, index_search);
                        reqinfo->mode = MODE_GET;
                        if (reqtmp)
                            ldata =
                                netsnmp_get_list_node(reqtmp->parent_data,
                                                      TABLE_ITERATOR_NAME);
                        if (!ldata) {
                            netsnmp_request_add_list_data(reqtmp,
                                                          netsnmp_create_data_list
                                                          (TABLE_ITERATOR_NAME,
                                                           callback_data_context,
                                                           NULL));
                        } else {
                            /* may have changed */
                            ldata->data = callback_data_context;
                        }

                        table_info->indexes = index_search;
                        for(i = table_reg_info->min_column;
                            i <= (int)table_reg_info->max_column; i++) {
                            myname[reginfo->rootoid_len + 1] = i;
                            table_info->colnum = i;
                            vb = reqtmp->requestvb =
                                SNMP_MALLOC_TYPEDEF(netsnmp_variable_list);
                            if (vb == NULL) {
                                /*
                                 * Cleanup 
                                 */
                                if (free_this_index_search)
                                    snmp_free_varbind
                                        (free_this_index_search);
                                return SNMP_ERR_GENERR;
                            }
                            vb->type = ASN_NULL;
                            snmp_set_var_objid(vb, myname, myname_len);
                            netsnmp_call_next_handler(handler, reginfo,
                                                      reqinfo, reqtmp);
                            reqtmp->requestvb = NULL;
                            reqtmp->processed = 0;
                            if (vb->type != ASN_NULL) { /* XXX, not all */
                                netsnmp_oid_stash_add_data(cinfo, myname,
                                                           myname_len, vb);
                            } else {
                                snmp_free_var(vb);
                            }
                        }
                        reqinfo->mode = MODE_GET_STASH;
                        break;
#endif  /* NETSNMP_FEATURE_REMOVE_STASH_CACHE */

                    case MODE_GETNEXT:
                        /* looking for "next" matches */
                        if (netsnmp_check_getnext_reply
                            (request, coloid, coloid_len, index_search,
                             &ti_info->results)) {
                            if (netsnmp_iterator_remember(request,
                                                          ti_info->
                                                          results->name,
                                                          ti_info->
                                                          results->
                                                          name_length,
                                                          callback_data_context,
                                                          callback_loop_context,
                                                          iinfo) == NULL) {
                                /*
                                 * Cleanup 
                                 */
                                if (free_this_index_search)
                                    snmp_free_varbind
                                        (free_this_index_search);
                                return SNMP_ERR_GENERR;
                            }
                            /*
                             *  If we've been told that the rows are sorted,
                             *   then the first valid one we find
                             *   must be the right one.
                             */
                            if (iinfo->flags & NETSNMP_ITERATOR_FLAG_SORTED)
                                request_count--;
                        
                        } else {
                            if (iinfo->free_data_context && callback_data_context) {
                                (iinfo->free_data_context)(callback_data_context,
                                                           iinfo);
                            }
                        }
                        break;

#ifndef NETSNMP_NO_WRITE_SUPPORT
                    case MODE_SET_RESERVE2:
                    case MODE_SET_FREE:
                    case MODE_SET_UNDO:
                    case MODE_SET_COMMIT:
                        /* needed processing already done in RESERVE1 */
                        break;
#endif /* NETSNMP_NO_WRITE_SUPPORT */

                    default:
                        snmp_log(LOG_ERR,
                                 "table_iterator called with unsupported mode\n");
                        break;  /* XXX return */
                
                    }
                }

                /* Is there any point in carrying on? */
                if (!request_count)
                    break;
                /* get the next search possibility */
                last_loop_context = callback_loop_context;
                index_search =
                    (iinfo->get_next_data_point) (&callback_loop_context,
                                                  &callback_data_context,
                                                  index_search, iinfo);
                if (iinfo->free_loop_context && last_loop_context &&
                    callback_data_context != last_loop_context) {
                    (iinfo->free_loop_context) (last_loop_context, iinfo);
                    last_loop_context = NULL;
                }
            }

            /* free loop context before going on */
            if (callback_loop_context && iinfo->free_loop_context_at_end) {
                (iinfo->free_loop_context_at_end) (callback_loop_context,
                                                   iinfo);
                callback_loop_context = NULL;
            }

            /* decide which (GETNEXT) requests are not yet filled */
            if (reqinfo->mode == MODE_GETNEXT) {
                for(request = requests ; request; request = request->next) {
                    if (request->processed)
                        continue;
                    ti_info = (ti_cache_info*)
                        netsnmp_request_get_list_data(request,
                                                      TI_REQUEST_CACHE);
                    if (!ti_info->results) {
                      int nc;
                        table_info = netsnmp_extract_table_info(request);
                        nc = netsnmp_table_next_column(table_info);
                        if (0 == nc) {
                            coloid[reginfo->rootoid_len+1] = table_info->colnum+1;
                            snmp_set_var_objid(request->requestvb,
                                               coloid, reginfo->rootoid_len+2);
                            request->processed = TABLE_ITERATOR_NOTAGAIN;
                            break;
                        } else {
                          table_info->colnum = nc;
                          hintok = 0;
                          notdone = 1;
                        }
                    }
                }
            }
        }
    }
