switch(addr->ss_family) {
        case AF_INET: {
            struct sockaddr_in *in4 = (struct sockaddr_in *)addr;
            struct sockaddr_in *lin4 = (struct sockaddr_in *)&listener->addr;
            if(in4->sin_addr.s_addr == lin4->sin_addr.s_addr &&
               in4->sin_port == lin4->sin_port ) {
                if(listener->F == NULL)
                    last_closed = listener;
                else
                    return(listener);
            }
            break;
        }
#ifdef RB_IPV6
        case AF_INET6: {
            struct sockaddr_in6 *in6 = (struct sockaddr_in6 *)addr;
            struct sockaddr_in6 *lin6 =(struct sockaddr_in6 *)&listener->addr;
            if(IN6_ARE_ADDR_EQUAL(&in6->sin6_addr, &lin6->sin6_addr) &&
               in6->sin6_port == lin6->sin6_port) {
                if(listener->F == NULL)
                    last_closed = listener;
                else
                    return(listener);
            }
            break;

        }
#endif

        default:
            break;
        }
