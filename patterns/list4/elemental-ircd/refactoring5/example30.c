#ifdef RB_IPV6
if(type == HM_IPV6)
            aconf = find_dline((struct sockaddr *)&ip, AF_INET6);
        else
#endif
            aconf = find_dline((struct sockaddr *)&ip, AF_INET);
