switch (type)
    {
        case SCP_ADDRESS_TYPE_IPV4:
            /* convert from char to 32bit*/
            ret = inet_pton(AF_INET, addr, &ip4);

            if (ret == 0)
            {
                log_message(LOG_LEVEL_WARNING, "[session:%d] set_addr: invalid address", __LINE__);
                inet_pton(AF_INET, "127.0.0.1", &ip4);
                g_memcpy(&(s->ipv4addr), &(ip4.s_addr), 4);
                return 1;
            }

            g_memcpy(&(s->ipv4addr), &(ip4.s_addr), 4);
            break;
        case SCP_ADDRESS_TYPE_IPV4_BIN:
            g_memcpy(&(s->ipv4addr), addr, 4);
            break;
#ifdef IN6ADDR_ANY_INIT
        case SCP_ADDRESS_TYPE_IPV6:
            /* convert from char to 128bit*/
            ret = inet_pton(AF_INET6, addr, &ip6);

            if (ret == 0)
            {
                log_message(LOG_LEVEL_WARNING, "[session:%d] set_addr: invalid address", __LINE__);
                inet_pton(AF_INET, "::1", &ip6);
                g_memcpy(s->ipv6addr, &(ip6.s6_addr), 16);
                return 1;
            }

            g_memcpy(s->ipv6addr, &(ip6.s6_addr), 16);
            break;
        case SCP_ADDRESS_TYPE_IPV6_BIN:
            g_memcpy(s->ipv6addr, addr, 16);
            break;
#endif
        default:
            return 1;
    }
