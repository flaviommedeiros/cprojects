#ifndef NETSNMP_NO_WRITE_SUPPORT
if (MODE_IS_SET(agtreq_info->mode)) {
        /*
         * netsnmp_mutex_lock(&tad->lock);
         */
        rc = process_set_requests(agtreq_info, requests,
                                  tad, handler->handler_name);
        /*
         * netsnmp_mutex_unlock(&tad->lock);
         */
    } else
#endif /* NETSNMP_NO_WRITE_SUPPORT */
        rc = process_get_requests(reginfo, agtreq_info, requests, tad);
