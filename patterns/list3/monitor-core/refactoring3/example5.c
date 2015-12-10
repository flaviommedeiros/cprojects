switch (ifr->ifr_addr.sa_family) {
#ifdef  IPV6
                case AF_INET6:
                        len = sizeof(struct sockaddr_in6);
                        break;
#endif /* IPV6 */
                case AF_INET:
                default:
                        len = sizeof(struct sockaddr);
                        break;
                }
