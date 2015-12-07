#ifndef NETSNMP_NO_WRITE_SUPPORT
if ( MODE_IS_SET(reqinfo->mode) &&
         (reqinfo->mode != MODE_SET_RESERVE1)) {
        /*
         * for later set modes, we can skip all the index parsing,
         * and we always need to let child handlers have a chance
         * to clean up, if they were called in the first place (i.e. have
         * a valid table info pointer).
         */
        if(NULL == netsnmp_extract_table_info(requests)) {
            DEBUGMSGTL(("helper:table","no table info for set - skipping\n"));
        }
        else
            need_processing = 1;
    }
    else {
#endif /* NETSNMP_NO_WRITE_SUPPORT */
        /*
         * for GETS, only continue if we have at least one valid request.
         * for RESERVE1, only continue if we have indexes for all requests.
         */
           
    /*
     * loop through requests
     */

    for (request = requests; request; request = request->next) {
        netsnmp_variable_list *var = request->requestvb;

        DEBUGMSGOID(("verbose:table", var->name, var->name_length));
        DEBUGMSG(("verbose:table", "\n"));

        if (request->processed) {
            DEBUGMSG(("verbose:table", "already processed\n"));
            continue;
        }
        netsnmp_assert(request->status == SNMP_ERR_NOERROR);

        /*
         * this should probably be handled further up 
         */
        if ((reqinfo->mode == MODE_GET) && (var->type != ASN_NULL)) {
            /*
             * valid request if ASN_NULL 
             */
            DEBUGMSGTL(("helper:table",
                        "  GET var type is not ASN_NULL\n"));
            netsnmp_set_request_error(reqinfo, request,
                                      SNMP_ERR_WRONGTYPE);
            continue;
        }

#ifndef NETSNMP_NO_WRITE_SUPPORT
        if (reqinfo->mode == MODE_SET_RESERVE1) {
            DEBUGIF("helper:table:set") {
                u_char         *buf = NULL;
                size_t          buf_len = 0, out_len = 0;
                DEBUGMSGTL(("helper:table:set", " SET_REQUEST for OID: "));
                DEBUGMSGOID(("helper:table:set", var->name, var->name_length));
                out_len = 0;
                if (sprint_realloc_by_type(&buf, &buf_len, &out_len, 1,
                                           var, NULL, NULL, NULL)) {
                    DEBUGMSG(("helper:table:set"," type=%d(%02x), value=%s\n",
                              var->type, var->type, buf));
                } else {
                    if (buf != NULL) {
                        DEBUGMSG(("helper:table:set",
                                  " type=%d(%02x), value=%s [TRUNCATED]\n",
                                  var->type, var->type, buf));
                    } else {
                        DEBUGMSG(("helper:table:set",
                                  " type=%d(%02x), value=[NIL] [TRUNCATED]\n",
                                  var->type, var->type));
                    }
                }
                if (buf != NULL) {
                    free(buf);
                }
            }
        }
#endif /* NETSNMP_NO_WRITE_SUPPORT */

        /*
         * check to make sure its in table range 
         */

        out_of_range = 0;
        /*
         * if our root oid is > var->name and this is not a GETNEXT, 
         * then the oid is out of range. (only compare up to shorter 
         * length) 
         */
        if (reginfo->rootoid_len > var->name_length)
            tmp_len = var->name_length;
        else
            tmp_len = reginfo->rootoid_len;
        if (snmp_oid_compare(reginfo->rootoid, reginfo->rootoid_len,
                             var->name, tmp_len) > 0) {
            if (reqinfo->mode == MODE_GETNEXT) {
                if (var->name != var->name_loc)
                    SNMP_FREE(var->name);
                snmp_set_var_objid(var, reginfo->rootoid,
                                   reginfo->rootoid_len);
            } else {
                DEBUGMSGTL(("helper:table", "  oid is out of range.\n"));
                out_of_range = 1;
            }
        }
        /*
         * if var->name is longer than the root, make sure it is 
         * table.1 (table.ENTRY).  
         */
        else if ((var->name_length > reginfo->rootoid_len) &&
                 (var->name[reginfo->rootoid_len] != 1)) {
            if ((var->name[reginfo->rootoid_len] < 1) &&
                (reqinfo->mode == MODE_GETNEXT)) {
                var->name[reginfo->rootoid_len] = 1;
                var->name_length = reginfo->rootoid_len;
            } else {
                out_of_range = 1;
                DEBUGMSGTL(("helper:table", "  oid is out of range.\n"));
            }
        }
        /*
         * if it is not in range, then mark it in the request list 
         * because we can't process it, and set an error so
         * nobody else wastes time trying to process it either.  
         */
        if (out_of_range) {
            DEBUGMSGTL(("helper:table", "  Not processed: "));
            DEBUGMSGOID(("helper:table", var->name, var->name_length));
            DEBUGMSG(("helper:table", "\n"));

            /*
             *  Reject requests of the form 'myTable.N'   (N != 1)
             */
#ifndef NETSNMP_NO_WRITE_SUPPORT
            if (reqinfo->mode == MODE_SET_RESERVE1)
                table_helper_cleanup(reqinfo, request,
                                     SNMP_ERR_NOTWRITABLE);
            else
#endif /* NETSNMP_NO_WRITE_SUPPORT */
            if (reqinfo->mode == MODE_GET)
                table_helper_cleanup(reqinfo, request,
                                     SNMP_NOSUCHOBJECT);
            continue;
        }


        /*
         * Check column ranges; set-up to pull out indexes from OID. 
         */

        incomplete = 0;
        tbl_req_info = netsnmp_extract_table_info(request);
        if (NULL == tbl_req_info) {
            tbl_req_info = SNMP_MALLOC_TYPEDEF(netsnmp_table_request_info);
            if (tbl_req_info == NULL) {
                table_helper_cleanup(reqinfo, request,
                                     SNMP_ERR_GENERR);
                continue;
            }
            tbl_req_info->reg_info = tbl_info;
            tbl_req_info->indexes = snmp_clone_varbind(tbl_info->indexes);
            tbl_req_info->number_indexes = 0;       /* none yet */
            netsnmp_request_add_list_data(request,
                                          netsnmp_create_data_list
                                          (TABLE_HANDLER_NAME,
                                           (void *) tbl_req_info,
                                           table_data_free_func));
        } else {
            DEBUGMSGTL(("helper:table", "  using existing tbl_req_info\n "));
        }

        /*
         * do we have a column?
         */
        if (var->name_length > oid_column_pos) {
            /*
             * oid is long enough to contain COLUMN info
             */
            DEBUGMSGTL(("helper:table:col",
                        "  have at least a column (%" NETSNMP_PRIo "d)\n",
                        var->name[oid_column_pos]));
            if (var->name[oid_column_pos] < tbl_info->min_column) {
                DEBUGMSGTL(("helper:table:col",
                            "    but it's less than min (%d)\n",
                            tbl_info->min_column));
                if (reqinfo->mode == MODE_GETNEXT) {
                    /*
                     * fix column, truncate useless column info 
                     */
                    var->name_length = oid_column_pos;
                    tbl_req_info->colnum = tbl_info->min_column;
                } else
                    out_of_range = 1;
            } else if (var->name[oid_column_pos] > tbl_info->max_column)
                out_of_range = 1;
            else
                tbl_req_info->colnum = var->name[oid_column_pos];

            if (out_of_range) {
                /*
                 * this is out of range...  remove from requests, free
                 * memory 
                 */
                DEBUGMSGTL(("helper:table",
                            "    oid is out of range. Not processed: "));
                DEBUGMSGOID(("helper:table", var->name, var->name_length));
                DEBUGMSG(("helper:table", "\n"));

                /*
                 *  Reject requests of the form 'myEntry.N'   (invalid N)
                 */
#ifndef NETSNMP_NO_WRITE_SUPPORT
                if (reqinfo->mode == MODE_SET_RESERVE1)
                    table_helper_cleanup(reqinfo, request,
                                         SNMP_ERR_NOTWRITABLE);
                else if (reqinfo->mode == MODE_GET)
#endif /* NETSNMP_NO_WRITE_SUPPORT */
                    table_helper_cleanup(reqinfo, request,
                                         SNMP_NOSUCHOBJECT);
                continue;
            }
            /*
             * use column verification 
             */
            else if (tbl_info->valid_columns) {
                tbl_req_info->colnum =
                    netsnmp_closest_column(var->name[oid_column_pos],
                                           tbl_info->valid_columns);
                DEBUGMSGTL(("helper:table:col", "    closest column is %d\n",
                            tbl_req_info->colnum));
                /*
                 * xxx-rks: document why the continue...
                 */
                if (tbl_req_info->colnum == 0)
                    continue;
                if (tbl_req_info->colnum != var->name[oid_column_pos]) {
                    DEBUGMSGTL(("helper:table:col",
                                "    which doesn't match req "
                                "%" NETSNMP_PRIo "d - truncating index info\n",
                                var->name[oid_column_pos]));
                    /*
                     * different column! truncate useless index info 
                     */
                    var->name_length = oid_column_pos + 1; /* pos is 0 based */
                }
            }
            /*
             * var->name_length may have changed - check again 
             */
            if ((int)var->name_length <= oid_index_pos) { /* pos is 0 based */
                DEBUGMSGTL(("helper:table", "    not enough for indexes\n"));
                tbl_req_info->index_oid_len = 0; /** none available */
            } else {
                /*
                 * oid is long enough to contain INDEX info
                 */
                tbl_req_info->index_oid_len =
                    var->name_length - oid_index_pos;
                DEBUGMSGTL(("helper:table", "    have %lu bytes of index\n",
                            (unsigned long)tbl_req_info->index_oid_len));
                netsnmp_assert(tbl_req_info->index_oid_len < MAX_OID_LEN);
                memcpy(tbl_req_info->index_oid, &var->name[oid_index_pos],
                       tbl_req_info->index_oid_len * sizeof(oid));
                tmp_name = tbl_req_info->index_oid;
            }
        } else if (reqinfo->mode == MODE_GETNEXT ||
                   reqinfo->mode == MODE_GETBULK) {
            /*
             * oid is NOT long enough to contain column or index info, so start
             * at the minimum column. Set index oid len to 0 because we don't
             * have any index info in the OID.
             */
            DEBUGMSGTL(("helper:table", "  no column/index in request\n"));
            tbl_req_info->index_oid_len = 0;
            tbl_req_info->colnum = tbl_info->min_column;
        } else {
            /*
             * oid is NOT long enough to contain index info,
             * so we can't do anything with it.
             *
             * Reject requests of the form 'myTable' or 'myEntry'
             */
            if (reqinfo->mode == MODE_GET ) {
                table_helper_cleanup(reqinfo, request, SNMP_NOSUCHOBJECT);
#ifndef NETSNMP_NO_WRITE_SUPPORT
            } else if (reqinfo->mode == MODE_SET_RESERVE1 ) {
                table_helper_cleanup(reqinfo, request, SNMP_ERR_NOTWRITABLE);
#endif /* NETSNMP_NO_WRITE_SUPPORT */
            }
            continue;
        }

        /*
         * set up tmp_len to be the number of OIDs we have beyond the column;
         * these should be the index(s) for the table. If the index_oid_len
         * is 0, set tmp_len to -1 so that when we try to parse the index below,
         * we just zero fill everything.
         */
        if (tbl_req_info->index_oid_len == 0) {
            incomplete = 1;
            tmp_len = -1;
        } else
            tmp_len = tbl_req_info->index_oid_len;


        /*
         * for each index type, try to extract the index from var->name
         */
        DEBUGMSGTL(("helper:table", "  looking for %d indexes\n",
                    tbl_info->number_indexes));
        for (tmp_idx = 0, vb = tbl_req_info->indexes;
             tmp_idx < tbl_info->number_indexes;
             ++tmp_idx, vb = vb->next_variable) {
            size_t parsed_oid_len;

            if (incomplete && tmp_len) {
                /*
                 * incomplete/illegal OID, set up dummy 0 to parse 
                 */
                DEBUGMSGTL(("helper:table",
                            "  oid indexes not complete: "));
                DEBUGMSGOID(("helper:table", var->name, var->name_length));
                DEBUGMSG(("helper:table", "\n"));

                /*
                 * no sense in trying anymore if this is a GET/SET. 
                 *
                 * Reject requests of the form 'myObject'   (no instance)
                 */
                tmp_len = 0;
                tmp_name = NULL;
                break;
            }
            /*
             * try and parse current index 
             */
            netsnmp_assert(tmp_len >= 0);
            parsed_oid_len = tmp_len;
            if (parse_one_oid_index(&tmp_name, &parsed_oid_len,
                                    vb, 1) != SNMPERR_SUCCESS) {
                incomplete = 1;
                tmp_len = -1;   /* is this necessary? Better safe than
                                 * sorry */
            } else {
                tmp_len = parsed_oid_len;
                DEBUGMSGTL(("helper:table", "  got 1 (incomplete=%d)\n",
                            incomplete));
                /*
                 * do not count incomplete indexes 
                 */
                if (incomplete)
                    continue;
                ++tbl_req_info->number_indexes; /** got one ok */
                if (tmp_len <= 0) {
                    incomplete = 1;
                    tmp_len = -1;       /* is this necessary? Better safe
                                         * than sorry */
                }
            }
        }                       /** for loop */

        DEBUGIF("helper:table:results") {
                unsigned int    count;
                u_char         *buf = NULL;
                size_t          buf_len = 0, out_len = 0;
                DEBUGMSGTL(("helper:table:results", "  found %d indexes\n",
                            tbl_req_info->number_indexes));
                DEBUGMSGTL(("helper:table:results",
                            "  column: %d, indexes: %d",
                            tbl_req_info->colnum,
                            tbl_req_info->number_indexes));
                for (vb = tbl_req_info->indexes, count = 0;
                     vb && count < tbl_req_info->number_indexes;
                     count++, vb = vb->next_variable) {
                    out_len = 0;
                    if (sprint_realloc_by_type(&buf, &buf_len, &out_len, 1,
                                               vb, NULL, NULL, NULL)) {
                        DEBUGMSG(("helper:table:results",
                                  "   index: type=%d(%02x), value=%s",
                                  vb->type, vb->type, buf));
                    } else {
                        if (buf != NULL) {
                            DEBUGMSG(("helper:table:results",
                                      "   index: type=%d(%02x), value=%s [TRUNCATED]",
                                      vb->type, vb->type, buf));
                        } else {
                            DEBUGMSG(("helper:table:results",
                                      "   index: type=%d(%02x), value=[NIL] [TRUNCATED]",
                                      vb->type, vb->type));
                        }
                    }
                }
                if (buf != NULL) {
                    free(buf);
                }
                DEBUGMSG(("helper:table:results", "\n"));
        }


        /*
         * do we have sufficient index info to continue?
         */

        if ((reqinfo->mode != MODE_GETNEXT) &&
            ((tbl_req_info->number_indexes != tbl_info->number_indexes) ||
             (tmp_len != -1))) {

            DEBUGMSGTL(("helper:table",
                        "invalid index(es) for table - skipping\n"));

#ifndef NETSNMP_NO_WRITE_SUPPORT
            if ( MODE_IS_SET(reqinfo->mode) ) {
                /*
                 * no point in continuing without indexes for set.
                 */
                netsnmp_assert(reqinfo->mode == MODE_SET_RESERVE1);
                /** clear first request so we wont try to run FREE mode */
                netsnmp_free_request_data_sets(requests);
                /** set actual error */
                table_helper_cleanup(reqinfo, request, SNMP_ERR_NOCREATION);
                need_processing = 0; /* don't call next handler */
                break;
            }
#endif /* NETSNMP_NO_WRITE_SUPPORT */
            table_helper_cleanup(reqinfo, request, SNMP_NOSUCHINSTANCE);
            continue;
        }
        netsnmp_assert(request->status == SNMP_ERR_NOERROR);
        
        ++need_processing;

    }                           /* for each request */
#ifndef NETSNMP_NO_WRITE_SUPPORT
    }
