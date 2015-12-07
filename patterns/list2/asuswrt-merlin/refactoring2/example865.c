#ifdef netbsd1
if (sa->sa_family == AF_INET)
#endif
                        if (in_ifaddr.ia_ifp == ifnetaddr) {
                            has_ipaddr = 1;     /* this IF has IP-address */
                            break;
                        }
