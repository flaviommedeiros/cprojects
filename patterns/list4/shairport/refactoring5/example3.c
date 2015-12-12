#ifdef AF_INET6
if (fdsa.SAFAMILY == AF_INET6) {
        struct sockaddr_in6 *sa6 = (struct sockaddr_in6*)(&fdsa);
        memcpy(bp, sa6->sin6_addr.s6_addr, 16);
        bp += 16;
    } else
#endif
    {
        struct sockaddr_in *sa = (struct sockaddr_in*)(&fdsa);
        memcpy(bp, &sa->sin_addr.s_addr, 4);
        bp += 4;
    }
