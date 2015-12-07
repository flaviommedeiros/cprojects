if (MODE_IS_GET(save_mode)
#ifndef NETSNMP_NO_WRITE_SUPPORT
            || (save_mode < SNMP_MSG_INTERNAL_SET_COMMIT)
#endif /* NETSNMP_NO_WRITE_SUPPORT */
            ) {
            rc = netsnmp_check_requests_error(requests);
            if(rc) {
                DEBUGMSGTL(("baby_steps", "   ERROR:request error\n"));
                break;
            }
        }
