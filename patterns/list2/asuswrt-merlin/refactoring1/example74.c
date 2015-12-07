if ((from_addr->sa.sa_family == AF_INET) &&
            ((cachep->sas.sin.sin_addr.s_addr !=
              from_addr->sin.sin_addr.s_addr) ||
             (cachep->sas.sin.sin_port != from_addr->sin.sin_port)))
                continue;
#ifdef NETSNMP_TRANSPORT_UDPIPV6_DOMAIN
        else if ((from_addr->sa.sa_family == AF_INET6) &&
                 ((cachep->sas.sin6.sin6_port != from_addr->sin6.sin6_port) ||
                  (cachep->sas.sin6.sin6_scope_id !=
                   from_addr->sin6.sin6_scope_id) ||
                  (memcmp(cachep->sas.sin6.sin6_addr.s6_addr,
                          from_addr->sin6.sin6_addr.s6_addr,
                          sizeof(from_addr->sin6.sin6_addr.s6_addr)) != 0)))
            continue;
#endif
