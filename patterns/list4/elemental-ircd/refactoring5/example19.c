#ifdef RB_IPV6
if(listener->addr.ss_family == AF_INET6) {
        struct sockaddr_in6 *in6 = (struct sockaddr_in6 *)&listener->addr;
        if(!IN6_ARE_ADDR_EQUAL(&in6->sin6_addr, &in6addr_any)) {
            rb_inet_ntop(AF_INET6, &in6->sin6_addr, listener->vhost, sizeof(listener->vhost));
            listener->name = listener->vhost;
        }
    } else
#endif
    {
        struct sockaddr_in *in = (struct sockaddr_in *)&listener->addr;
        if(in->sin_addr.s_addr != INADDR_ANY) {
            rb_inet_ntop(AF_INET, &in->sin_addr, listener->vhost, sizeof(listener->vhost));
            listener->name = listener->vhost;
        }
    }
