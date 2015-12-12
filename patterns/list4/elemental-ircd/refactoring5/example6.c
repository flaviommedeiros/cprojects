#ifdef RB_IPV6
if(strchr(ip, ':')) {
        if((ptr = strchr(ip, '/'))) {
            *ptr = '\0';
            ptr++;
            *b = atoi(ptr);
            if(*b > 128)
                *b = 128;
        } else
            *b = 128;
        if(rb_inet_pton_sock(ip, (struct sockaddr *)addr) > 0)
            return HM_IPV6;
        else
            return HM_HOST;
    } else
#endif
        if(strchr(text, '.')) {
            if((ptr = strchr(ip, '/'))) {
                *ptr = '\0';
                ptr++;
                *b = atoi(ptr);
                if(*b > 32)
                    *b = 32;
            } else
                *b = 32;
            if(rb_inet_pton_sock(ip, (struct sockaddr *)addr) > 0)
                return HM_IPV4;
            else
                return HM_HOST;
        }
