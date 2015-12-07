if(MODE_IS_GET(oldmode)
#ifndef NETSNMP_NO_WRITE_SUPPORT
       || (MODE_SET_RESERVE1 == oldmode)
#endif /* NETSNMP_NO_WRITE_SUPPORT */
        ) {
        netsnmp_request_info *curr_request;
        /*
         * Loop through each of the requests, and
         * try to find the appropriate row from the container.
         */
        for (curr_request = requests; curr_request; curr_request = curr_request->next) {
            /*
             * skip anything that doesn't need processing.
             */
            if (curr_request->processed != 0) {
                DEBUGMSGTL(("table_container", "already processed\n"));
                continue;
            }
            
            /*
             * find data for this request
             */
            _data_lookup(reginfo, agtreq_info, curr_request, tad);

            if(curr_request->processed)
                continue;

            ++need_processing;
        } /** for ( ... requests ... ) */
    }
