#ifdef RB_IPV6
if(strchr(listener_address, ':') != NULL)
                family = AF_INET6;
            else
#endif
                family = AF_INET;
