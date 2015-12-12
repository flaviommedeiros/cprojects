switch(a->addr->sa_family) {
      case AF_INET:
        printf("\tAddress Family: AF_INET\n");
        if (a->addr)
          printf("\t\tAddress: %s\n",
            inet_ntoa(((struct sockaddr_in *)(a->addr))->sin_addr));
        if (a->netmask)
          printf("\t\tNetmask: %s\n",
            inet_ntoa(((struct sockaddr_in *)(a->netmask))->sin_addr));
        if (a->broadaddr)
          printf("\t\tBroadcast Address: %s\n",
            inet_ntoa(((struct sockaddr_in *)(a->broadaddr))->sin_addr));
        if (a->dstaddr)
          printf("\t\tDestination Address: %s\n",
            inet_ntoa(((struct sockaddr_in *)(a->dstaddr))->sin_addr));
        break;
#ifdef INET6
      case AF_INET6:
        printf("\tAddress Family: AF_INET6\n");
        if (a->addr)
          printf("\t\tAddress: %s\n",
            inet_ntop(AF_INET6,
               ((struct sockaddr_in6 *)(a->addr))->sin6_addr.s6_addr,
               ntop_buf, sizeof ntop_buf));
        if (a->netmask)
          printf("\t\tNetmask: %s\n",
            inet_ntop(AF_INET6,
              ((struct sockaddr_in6 *)(a->netmask))->sin6_addr.s6_addr,
               ntop_buf, sizeof ntop_buf));
        if (a->broadaddr)
          printf("\t\tBroadcast Address: %s\n",
            inet_ntop(AF_INET6,
              ((struct sockaddr_in6 *)(a->broadaddr))->sin6_addr.s6_addr,
               ntop_buf, sizeof ntop_buf));
        if (a->dstaddr)
          printf("\t\tDestination Address: %s\n",
            inet_ntop(AF_INET6,
              ((struct sockaddr_in6 *)(a->dstaddr))->sin6_addr.s6_addr,
               ntop_buf, sizeof ntop_buf));
        break;
#endif
      default:
        printf("\tAddress Family: Unknown (%d)\n", a->addr->sa_family);
        break;
      }
