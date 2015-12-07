if (cur->family == AF_INET6
#ifdef HAVE_SOCKADDR_IN6_SCOPE_ID
              && cur->ipv6_scope == ip->ipv6_scope
#endif
              && IN6_ARE_ADDR_EQUAL (&cur->data.d6, &ip->data.d6))
            return true;
